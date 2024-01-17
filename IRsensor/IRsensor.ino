#include <IRremote.h>
#define IR_RECEIVE_PIN 3
int bottom=13;
int bottomLeft=12;
int bottomRight=11;
int middle=10;
int topLeft=9;
int top=8;
int topRight=7;

int isOne=0;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);

  
  pinMode(bottom, OUTPUT);
  pinMode(bottomLeft, OUTPUT);
  pinMode(bottomRight, OUTPUT);
  pinMode(middle, OUTPUT);
  pinMode(topLeft, OUTPUT);
  pinMode(top, OUTPUT);
  pinMode(topRight, OUTPUT);
  nul();

  pinMode(2, OUTPUT);
}
void loop() {

  if (IrReceiver.decode()) {
    
    if(IrReceiver.decodedIRData.command == 129){
      if(isOne == 0){
        Serial.println("129 ON");
        reset();
        en();
        isOne = 1;
        Serial.println(isOne);
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
      }
      else {
        Serial.println("OFF");
        reset();
        nul();
        isOne = 0;
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        
      }   
    }
    IrReceiver.resume();
    //taelTilNi();
    Serial.println(IrReceiver.decodedIRData.command);

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