#include<LiquidCrystal.h>

#define floorOne 8
#define floorTwo 9
#define floorThree 10
#define floorFour 11

int indicatorOne = 3;
int indicatorTwo = 7;
int indicatorThree = 11;
int indicatorFour = 15;

int pastOne, pastTwo, pastThree, pastFour = 1;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  pinMode(floorOne, INPUT);
  pinMode(floorTwo, INPUT);
  pinMode(floorThree, INPUT);
  pinMode(floorFour, INPUT);
  populateLCD();
}

void loop() {
  int currentOne = digitalRead(floorOne);
  if (currentOne != pastOne) {
    lcd.setCursor(indicatorOne, 1);
    if (currentOne == 1) {
      lcd.print("K");
    }
    else {
      lcd.print("X");
    }
    pastOne = currentOne;
  }

  int currentTwo = digitalRead(floorTwo);
  if (currentTwo != pastTwo) {
    lcd.setCursor(indicatorTwo, 1);
    if (currentTwo == 1) {
      lcd.print("K");
    }
    else {
      lcd.print("X");
    }
    pastTwo = currentTwo;
  }

  int currentThree = digitalRead(floorThree);
  if (currentThree != pastThree) {
    lcd.setCursor(indicatorThree, 1);
    if (currentThree == 1) {
      lcd.print("K");
    }
    else {
      lcd.print("X");
    }
    pastThree = currentThree;
  }

  int currentFour = digitalRead(floorFour);
  if (currentFour != pastFour) {
    lcd.setCursor(indicatorFour, 1);
    if (currentFour == 1) {
      lcd.print("K");
    }
    else {
      lcd.print("X");
    }
    pastFour = currentFour;
  }
  if (pastOne and pastTwo and pastThree and pastFour) {
    lcd.setCursor(0, 2);
    lcd.print("ALL FLOORS OKAY!");
    lcd.setCursor(0, 3);
    lcd.print("                ");
  }
  else {
    lcd.setCursor(0, 2);
    lcd.print("ELEVATOR SENT TO");
    lcd.setCursor(0, 3);
    lcd.print("GROUND FLOOR.");
  }
}

void populateLCD() {
  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("F: 1 | 2 | 3 | 4");
  lcd.setCursor(0, 1);
  lcd.print("S: K | K | K | K");
  lcd.setCursor(0, 2);
  lcd.print("ALL FLOORS OKAY!");
  lcd.setCursor(0, 3);
  lcd.print("");
}
