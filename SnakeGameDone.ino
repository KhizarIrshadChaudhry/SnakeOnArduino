#include <LedControl.h>
#include <IRremote.h>
#define IR_RECEIVE_PIN 3 //Fjernbetjening reciever sensoren

//Syv segment display
int bottom=13;
int bottomLeft=12;
int bottomRight=11;
int middle=10;
int topLeft=9;
int top=8;
int topRight=7;
//Anden Syvsegments display (Ikke nødvendigt)
int Bbottom=40;
int BbottomLeft=41;
int BbottomRight=42;
int Bmiddle=43;
int BtopLeft=44;
int Btop=45;
int BtopRight=46;

//SLANGEN:
typedef struct Snake Snake;
struct Snake{
  int head[2];     // (row, column) af slangens hoved
  int body[40][2]; //Array med (row, column)
  int len;         //Længden af slangen 
  int dir[2];      //Retning af slangen
  int point;
  int pointDisplay;
  int BpointDisplay;
};

//APPLE:
typedef struct Apple Apple;
struct Apple{
  int rPos; //Row index af apple
  int cPos; //Column index af apple
};

//Pins til LED MATRIX
const int DIN =22;
const int CS =23;
const int CLK = 24;
LedControl lc = LedControl(DIN, CLK, CS,1);

int points=0; //Start fra 0 point til spilleren


byte pic[8] = {0,0,0,0,0,0,0,0};//De 8 rows af LED MATRIX'EN

Snake snake = {{1,5},{{0,5}, {1,5}}, 2, {1,0}};//Lav en slange
Apple apple = {(int)random(0,8),(int)random(0,8)};//Lav et æble

//Variablerne til spillets klokke
float oldTime = 0;
float timer = 0;
float updateRate = 3;

int i,j,num;//Counters
void setup() {

  num = 0;
  //Controls fra fjernbetjening
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);


  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);


  //Syv segment display setup af pins'ene
  pinMode(bottom, OUTPUT);
  pinMode(bottomLeft, OUTPUT);
  pinMode(bottomRight, OUTPUT);
  pinMode(middle, OUTPUT);
  pinMode(topLeft, OUTPUT);
  pinMode(top, OUTPUT);
  pinMode(topRight, OUTPUT);

  pinMode(Bbottom, OUTPUT);
  pinMode(BbottomLeft, OUTPUT);
  pinMode(BbottomRight, OUTPUT);
  pinMode(Bmiddle, OUTPUT);
  pinMode(BtopLeft, OUTPUT);
  pinMode(Btop, OUTPUT);
  pinMode(BtopRight, OUTPUT);


  nul(); //Start på nul
}

void loop() {
  float deltaTime = calculateDeltaTime();
  timer += deltaTime;

  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);  

    if(IrReceiver.decodedIRData.command == 199){
      snake.dir[0] = 0;
      snake.dir[1] = -1;
      Serial.println("DOWN");
    }else if(IrReceiver.decodedIRData.command == 198){
      snake.dir[0] = 0;
      snake.dir[1] = 1;
    }else if(IrReceiver.decodedIRData.command == 200){
      snake.dir[0] = -1;
      snake.dir[1] = 0;
    }else if(IrReceiver.decodedIRData.command == 201){
      snake.dir[0] = 1;
      snake.dir[1] = 0;} 
    IrReceiver.resume();
  }
  
  //Update
  if(timer > 1000/updateRate){
    timer = 0;
    Update();
  }
  
  //Render
  Render();
}


float calculateDeltaTime(){
  float currentTime = millis();
  float dt = currentTime - oldTime;
  oldTime = currentTime;
  return dt;
}

void reset(){
  for(int j=0;j<8;j++){
    pic[j] = 0;
  }
}
void Update(){
  reset();//0 alle
  
  int newHead[2] = {snake.head[0]+snake.dir[0], snake.head[1]+snake.dir[1]};

  //Handle Borders
  if(newHead[0]==8){
    updateRate=3;
    delay(500);
    resetSyvSegment();
    nul();

    BresetSyvSegment();
    Bnul();
    snake = {{1,5},{{0,5}, {1,5}}, 2, {1,0}};//slange ny
    apple = {(int)random(0,8),(int)random(0,8)};//Nyt æble
    return;
  }else if(newHead[0]==-1){
    updateRate=3;
    delay(1500);
    resetSyvSegment();
    BresetSyvSegment();
    delay(500);
    nul();
    Bnul();
    snake = {{1,5},{{0,5}, {1,5}}, 2, {1,0}};//slange ny
    apple = {(int)random(0,8),(int)random(0,8)};//Nyt æble
    return;
  }else if(newHead[1]==8){
    updateRate=3;
    delay(1500);
    resetSyvSegment();
    BresetSyvSegment();
    delay(500);
    nul();
    Bnul();
    snake = {{1,5},{{0,5}, {1,5}}, 2, {1,0}};//slange ny
    apple = {(int)random(0,8),(int)random(0,8)};//Nyt æble
    return;
  }else if(newHead[1]==-1){
    updateRate=3;
    delay(1500);
    resetSyvSegment();
    BresetSyvSegment();
    delay(500);
    nul();
    Bnul();
    snake = {{1,5},{{0,5}, {1,5}}, 2, {1,0}};//slange ny
    apple = {(int)random(0,8),(int)random(0,8)};//Nyt æble
    return;
  }
  
  //Hvis slangen slår sig selv (Død)
   for(j=0;j<snake.len;j++){
    if(snake.body[j][0] == newHead[0] && snake.body[j][1] == newHead[1]){
      //stop spillet
      updateRate=3;

      delay(1500);
      resetSyvSegment();
      BresetSyvSegment();
      delay(1500);
      nul();
      Bnul();
      snake = {{1,5},{{0,5}, {1,5}}, 2, {1,0}};//slange ny
      apple = {(int)random(0,8),(int)random(0,8)};//Nyt æble
      return;
    }
  }

  //Check hvis apple er spist 
  if(newHead[0] == apple.rPos && newHead[1] ==apple.cPos){

    updateRate+=0.3;
    snake.point = snake.point+1;
    snake.pointDisplay++;
    snake.BpointDisplay++;
    if(snake.pointDisplay>9){
      snake.pointDisplay=0;
      snake.BpointDisplay++;
    }
    BdisplaySyvSegment(snake.BpointDisplay);
    displaySyvSegment(snake.pointDisplay);

    snake.len = snake.len+1;
    apple.rPos = (int)random(0,8);
    apple.cPos = (int)random(0,8);



  }else{
    removeFirst();//Shifting array til højre
  }
  
  snake.body[snake.len-1][0]= newHead[0];
  snake.body[snake.len-1][1]= newHead[1];
  
  snake.head[0] = newHead[0];
  snake.head[1] = newHead[1];
  
  // Display(slange og æble)
  for(j=0;j<snake.len;j++){
    pic[snake.body[j][0]] |= 128 >> snake.body[j][1];
  }
  pic[apple.rPos] |= 128 >> apple.cPos;
  
}

void Render(){
   for(i=0;i<8;i++){
    lc.setRow(0,i,pic[i]);
   }
}

void removeFirst(){
  for(j=1;j<snake.len;j++){
    snake.body[j-1][0] = snake.body[j][0];
    snake.body[j-1][1] = snake.body[j][1];
  }
}





//Syv segments funktioner
void resetSyvSegment(void){
  digitalWrite(bottom, LOW);
  digitalWrite(bottomLeft, LOW);
  digitalWrite(bottomRight, LOW);
  digitalWrite(middle, LOW);
  digitalWrite(topLeft, LOW);
  digitalWrite(top, LOW);
  digitalWrite(topRight, LOW);
}

void nul(void){
  digitalWrite(top, HIGH);
  digitalWrite(bottom, HIGH);

  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);

  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void en(void){
  digitalWrite(bottomRight, HIGH);
  digitalWrite(topRight, HIGH);
}

void to(void){
  digitalWrite(top, HIGH);
  digitalWrite(bottom, HIGH);
  digitalWrite(middle, HIGH);

  digitalWrite(topRight, HIGH);
  digitalWrite(bottomLeft, HIGH);
}

void tre(void){
  digitalWrite(top, HIGH);
  digitalWrite(bottom, HIGH);
  digitalWrite(middle, HIGH);

  digitalWrite(topRight, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void fire(void){
  digitalWrite(middle, HIGH);

  digitalWrite(topRight, HIGH);
  digitalWrite(topLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}


void fem(void){
  digitalWrite(top, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottom, HIGH);

  digitalWrite(topLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void seks(void){
  digitalWrite(top, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottom, HIGH);

  digitalWrite(topLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
  digitalWrite(bottomLeft, HIGH);
}


void syv(void){
  digitalWrite(top, HIGH);

  digitalWrite(topRight, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void otte(void){
  digitalWrite(top, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottom, HIGH);

  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);

  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void ni(void){
  digitalWrite(top, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottom, HIGH);

  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);

  digitalWrite(bottomRight, HIGH);
}




//En funktion jeg har lavet som omregner int til 7 segment
void displaySyvSegment(int tal) {
  switch (tal){
    case 0:
      resetSyvSegment();
      nul();
      break;
    case 1:
      resetSyvSegment();
      en();
      break;
    case 2:
      resetSyvSegment();
      to();
      break;
    case 3:
      resetSyvSegment();
      tre();
      break;
    case 4:
      resetSyvSegment();
      fire();
      break;
    case 5:
      resetSyvSegment();
      fem();
      break;
    case 6:
      resetSyvSegment();
      seks();
      break;
    case 7:
      resetSyvSegment();
      syv();
      break;
    case 8:
      resetSyvSegment();
      otte();
      break;
    case 9:
      resetSyvSegment();
      ni();
      break;
  }
}



//Anden Syv segments funktioner
void BresetSyvSegment(void){
  digitalWrite(Bbottom, LOW);
  digitalWrite(BbottomLeft, LOW);
  digitalWrite(BbottomRight, LOW);
  digitalWrite(Bmiddle, LOW);
  digitalWrite(BtopLeft, LOW);
  digitalWrite(Btop, LOW);
  digitalWrite(BtopRight, LOW);
}

void Bnul(void){
  digitalWrite(Btop, HIGH);
  digitalWrite(Bbottom, HIGH);

  digitalWrite(BtopLeft, HIGH);
  digitalWrite(BtopRight, HIGH);

  digitalWrite(BbottomLeft, HIGH);
  digitalWrite(BbottomRight, HIGH);
}

void Ben(void){
  digitalWrite(BbottomRight, HIGH);
  digitalWrite(BtopRight, HIGH);
}

void Bto(void){
  digitalWrite(Btop, HIGH);
  digitalWrite(Bbottom, HIGH);
  digitalWrite(Bmiddle, HIGH);

  digitalWrite(BtopRight, HIGH);
  digitalWrite(BbottomLeft, HIGH);
}

void Btre(void){
  digitalWrite(Btop, HIGH);
  digitalWrite(Bbottom, HIGH);
  digitalWrite(Bmiddle, HIGH);

  digitalWrite(BtopRight, HIGH);
  digitalWrite(BbottomRight, HIGH);
}

void Bfire(void){
  digitalWrite(Bmiddle, HIGH);

  digitalWrite(BtopRight, HIGH);
  digitalWrite(BtopLeft, HIGH);
  digitalWrite(BbottomRight, HIGH);
}


void Bfem(void){
  digitalWrite(Btop, HIGH);
  digitalWrite(Bmiddle, HIGH);
  digitalWrite(Bbottom, HIGH);

  digitalWrite(BtopLeft, HIGH);
  digitalWrite(BbottomRight, HIGH);
}

void Bseks(void){
  digitalWrite(Btop, HIGH);
  digitalWrite(Bmiddle, HIGH);
  digitalWrite(Bbottom, HIGH);

  digitalWrite(BtopLeft, HIGH);
  digitalWrite(BbottomRight, HIGH);
  digitalWrite(BbottomLeft, HIGH);
}


void Bsyv(void){
  digitalWrite(Btop, HIGH);

  digitalWrite(BtopRight, HIGH);
  digitalWrite(BbottomRight, HIGH);
}

void Botte(void){
  digitalWrite(Btop, HIGH);
  digitalWrite(Bmiddle, HIGH);
  digitalWrite(Bbottom, HIGH);

  digitalWrite(BtopLeft, HIGH);
  digitalWrite(BtopRight, HIGH);

  digitalWrite(BbottomLeft, HIGH);
  digitalWrite(BbottomRight, HIGH);
}

void Bni(void){
  digitalWrite(Btop, HIGH);
  digitalWrite(Bmiddle, HIGH);
  digitalWrite(Bbottom, HIGH);

  digitalWrite(BtopLeft, HIGH);
  digitalWrite(BtopRight, HIGH);

  digitalWrite(BbottomRight, HIGH);
}




//En funktion jeg har lavet som omregner int til 7 segment
void BdisplaySyvSegment(int tal) {
  switch (tal){
    case 0:
      BresetSyvSegment();
      Bnul();
      break;
    case 1:
      BresetSyvSegment();
      Ben();
      break;
    case 2:
      BresetSyvSegment();
      Bto();
      break;
    case 3:
      BresetSyvSegment();
      Btre();
      break;
    case 4:
      BresetSyvSegment();
      Bfire();
      break;
    case 5:
      BresetSyvSegment();
      Bfem();
      break;
    case 6:
      BresetSyvSegment();
      Bseks();
      break;
    case 7:
      BresetSyvSegment();
      Bsyv();
      break;
    case 8:
      BresetSyvSegment();
      Botte();
      break;
    case 9:
      BresetSyvSegment();
      Bni();
      break;
  }
}