#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
long cm, duration;
const int echoPin = 7;
const int trigPin = 6;
const int lm1 = 2;
const int lm2 = 3;
const int rm1 = 4;
const int rm2 = 5;

void setup() {
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds to send out the pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin and calculate the distance in cm
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) * 0.0343;
  
  // Check if the distance is less than 20 cm
  if (cm < 20) {
    stop_bot();
    delay(2000);
    go_back();
    delay(2000);
    stop_again();
    delay(1000);
    go_left();
    delay(1000);
  } else {
    go_straight();
    delay(1000);
  }
  
  // Print the distance in the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println("cm");
}

// Function to stop the bot
void stop_bot() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SOMETHING AHEAD");
  lcd.setCursor(0, 1);
  lcd.print("STOP!!");
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}

// Function to move the bot backwards
void go_back() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TAKING REVERSE");
  lcd.setCursor(0, 1);
  lcd.print(cm);
  digitalWrite(lm2, HIGH);
  digitalWrite(lm1, LOW);
  digitalWrite(rm2, HIGH);
  digitalWrite(rm1, LOW);
}

// Function to stop the bot (for a turn)
void stop_again() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BREAK FOR TURN");
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}

// Function to turn the bot left
void go_left() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TURNING LEFT");
  lcd.setCursor(0, 1);
  lcd.print(cm);
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

// Function to turn the bot right
void go_right() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TURNING RIGHT");
  lcd.setCursor(0, 1);
  lcd.print(cm);
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}

// Function to move the bot forward
void go_straight() {
  lcd.setCursor(0, 0);
  lcd.print("NOTHING AHEAD ");
  lcd.setCursor(0, 1);
  lcd.print("MOVING FORWARD");
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}
