#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
#include <string.h>  // Include this for strlen()

Servo myservo;
int pos = 0; // position of servo motor
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);
const byte rows = 4;
const byte cols = 3;

char key[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[rows] = {0, 1, 2, 3};
byte colPins[cols] = {4, 5, 6};
Keypad keypad = Keypad(makeKeymap(key), rowPins, colPins, rows, cols);
const char* password = "5564";
int currentposition = 0;

int red = 13;
int green = 12;

void setup() {
  displayscreen();
  myservo.attach(8); //Servo motor connection
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  if (currentposition == 0) {
    displayscreen();
  }
  int l ;
  char code = keypad.getKey();
  if (code != NO_KEY) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PASSWORD:");
    lcd.setCursor(7, 1);
    lcd.print(" ");
    lcd.setCursor(7, 1);
    for (l = 0; l <= currentposition; ++l) {
      lcd.print("*");
    }

    if (code == password[currentposition]) {
      ++currentposition;
      if (currentposition == strlen(password)) {
        unlockdoor();
        currentposition = 0;
      }
    } else {
      incorrect();
      currentposition = 0;
    }
  }
}

void unlockdoor() {
  delay(900);
  lcd.setCursor(0, 0);
  lcd.println(" ");
  lcd.setCursor(1, 0);
  lcd.print("Access Granted");
  lcd.setCursor(4, 1);
  lcd.println("WELCOME!!");
  lcd.setCursor(15, 1);
  lcd.println(" ");
  lcd.setCursor(16, 1);
  lcd.println(" ");
  lcd.setCursor(14, 1);
  lcd.println(" ");
  lcd.setCursor(13, 1);
  lcd.println(" ");

  for (pos = 180; pos >= 0; pos -= 5) {
    myservo.write(pos);
    delay(5);
  }
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  delay(2000);

  delay(1000);
  counterbeep();

  delay(1000);

  for (pos = 0; pos <= 180; pos += 5) {
    myservo.write(pos);
    delay(15);
  }
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  delay(500);
  currentposition = 0;

  lcd.clear();
  displayscreen();
}

void incorrect() {
  delay(500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CODE");
  lcd.setCursor(6, 0);
  lcd.print("INCORRECT");
  lcd.setCursor(15, 1);
  lcd.println(" ");
  lcd.setCursor(4, 1);
  lcd.println("TRY AGAIN !!!");

  lcd.setCursor(13, 1);
  lcd.println(" ");
  Serial.println("CODE INCORRECT YOU ARE UNAUTHORIZED");
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  delay(3000);
  lcd.clear();
  displayscreen();
}

void displayscreen() {
  lcd.setCursor(0, 0);
  lcd.println("*ENTER THE CODE*");
  lcd.setCursor(1, 1);
  lcd.println("TO OPEN DOOR!!");
}

void counterbeep() {
  delay(1200);

  lcd.clear();

  lcd.setCursor(2, 15);
  lcd.println(" ");
  lcd.setCursor(2, 14);
  lcd.println(" ");
  lcd.setCursor(2, 0);
  delay(200);
  lcd.println("GET IN WITHIN:::");

  lcd.setCursor(4, 1);
  lcd.print("5");
  delay(200);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1);
  lcd.print("4");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);

  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1);
  lcd.print("3");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);

  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1);
  lcd.print("2");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);

  lcd.setCursor(4, 1);
  lcd.print("1");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN::");

  delay(1000);
  delay(40);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("RE-LOCKING");
  delay(500);
  lcd.setCursor(12, 0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(13, 0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(14, 0);
  lcd.print(".");
  delay(400);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("LOCKED!");
  delay(440);
}

