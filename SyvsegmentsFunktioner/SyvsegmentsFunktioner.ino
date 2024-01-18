//Syv segment display
int bottom=13;
int bottomLeft=12;
int bottomRight=11;
int middle=10;
int topLeft=9;
int top=8;
int topRight=7;

void setup() {
  pinMode(bottom, OUTPUT);
  pinMode(bottomLeft, OUTPUT);
  pinMode(bottomRight, OUTPUT);
  pinMode(middle, OUTPUT);
  pinMode(topLeft, OUTPUT);
  pinMode(top, OUTPUT);
  pinMode(topRight, OUTPUT);
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