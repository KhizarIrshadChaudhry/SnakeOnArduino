int bottom=13;
int bottomLeft=12;
int bottomRight=11;
int middle=10;
int topLeft=9;
int top=8;
int topRight=7;



void setup() {
  // put your setup code here, to run once:
  pinMode(bottom, OUTPUT);
  pinMode(bottomLeft, OUTPUT);
  pinMode(bottomRight, OUTPUT);
  pinMode(middle, OUTPUT);
  pinMode(topLeft, OUTPUT);
  pinMode(top, OUTPUT);
  pinMode(topRight, OUTPUT);



  Serial.begin(9600);

}
void loop() {
  // put your main code here, to run repeatedly:
  taelTilNi();
  //display(sonarSensor());
  
  //if (irrecv.decode(&results)){
 //     Serial.println(results.value, HEX);
   //   irrecv.resume();
  //}   
}

void display(int tal) {
  switch (tal){
    case 0:
      reset();
      nul();
      break;
    case 1:
      reset();
      en();
      break;
    case 2:
      reset();
      to();
      break;
    case 3:
      reset();
      tre();
      break;
    case 4:
      reset();
      fire();
      break;
    case 5:
      reset();
      fem();
      break;
    case 6:
      reset();
      seks();
      break;
    case 7:
      reset();
      syv();
      break;
    case 8:
      reset();
      otte();
      break;
    case 9:
      reset();
      ni();
      break;
  }
}


void taelTilNi(void){
  en();
  delay(1000);
  reset();
  to();
  delay(1000);
  reset();
  tre();
  delay(1000);
  reset();
  fire();
  delay(1000);
  reset();
  fem();
  delay(1000);
  reset();
  seks();
  delay(1000);
  reset();
  syv();
  delay(1000);
  reset();
  otte();
  delay(1000);
  reset();
  ni();
  delay(1000);
  reset();
}

void reset(void){
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