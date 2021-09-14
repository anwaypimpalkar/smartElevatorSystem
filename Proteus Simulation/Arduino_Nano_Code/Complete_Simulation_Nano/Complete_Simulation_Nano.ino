//Shift Register Pins
int latchPin = 11; //pin 12 on the 595
int dataPin = 12; //pin 14 on the 595
int clockPin = 13; //pin 11 on the 595

int floorStatusPin = 7;

#define MQ2Pin 2
#define LM35Pin A6

void setup() {
  analogReference(INTERNAL);
  pinMode(latchPin, OUTPUT);
  pinMode(floorStatusPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(MQ2Pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int receivedFloor = readFloorNumber();
    setSevenSegmentDisplay(receivedFloor);
  }
  int smokeValue = checkSmokeDetector();
  float tempValue = getTempValue();
  if (smokeValue == 1 or tempValue > 45) {
    digitalWrite(floorStatusPin, LOW);
    setSevenSegmentDisplay(69);
  }
  else {
    digitalWrite(floorStatusPin, HIGH);
  }
}

int checkSmokeDetector() {
  return digitalRead(MQ2Pin);
}

float getTempValue() {
  int TempValue = analogRead(LM35Pin);
  float TempCel = TempValue /9.31;
  return TempCel;
}

int readFloorNumber() {
  int receivedFloor = Serial.read();
  Serial.print("Received: ");
  Serial.println(receivedFloor - 48);
  return receivedFloor;
}

void setSevenSegmentDisplay(int floorASCII) {
  if (floorASCII == 49) { //1
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 121);
    digitalWrite(latchPin, HIGH);
  }
  else if (floorASCII == 50) { //2
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 36);
    digitalWrite(latchPin, HIGH);
  }
  else if (floorASCII == 51) { //3
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 48);
    digitalWrite(latchPin, HIGH);
  }
  else if (floorASCII == 52) { //4
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 25);
    digitalWrite(latchPin, HIGH);
  }
  else if (floorASCII == 69) { //4
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 158);
    digitalWrite(latchPin, HIGH);
  }
}
