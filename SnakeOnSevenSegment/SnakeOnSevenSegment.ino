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

int pot=A1;
int delayINT;

void setup() {
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
  Serial.println(analogRead(pot));
  delayINT = analogRead(pot);
  snakeOnSevenSegment();
}


void phaseOne(void){
  digitalWrite(bottom, HIGH);
}

void phaseTwo(void){
  digitalWrite(bottomRight, HIGH);
}

void phaseThree(void){
  digitalWrite(middle, HIGH);
}

void phaseFour(void){
  digitalWrite(topLeft, HIGH);
} 

void phaseFive(void){
  digitalWrite(top, HIGH);
} 

void phaseSix(void){
  digitalWrite(topRight, HIGH);
} 

void phaseSeven(void){
  digitalWrite(middle, HIGH);
}

void phaseEight(void){
  digitalWrite(bottomLeft, HIGH);
}

void phaseNine(void){
  digitalWrite(bottom, HIGH);
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

void snakeOnSevenSegment(void){
  reset();
  phaseOne();
  delay(delayINT);
  reset();
  phaseTwo();
  delay(delayINT);
  reset();
  phaseThree();
  delay(delayINT);
  reset();
  phaseFour();
  delay(delayINT);
  reset();
  phaseFive();
  delay(delayINT);
  reset();
  phaseSix();
  delay(delayINT);
  reset();
  phaseSeven();
  delay(delayINT);
  reset();
  phaseEight();
  delay(delayINT);
  reset();
  phaseNine();

}


