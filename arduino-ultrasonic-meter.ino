#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the I2C address (usually 0x27 or 0x3F) and dimensions (16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define Ultrasonic Sensor pins
const int trigPin = 9;
const int echoPin = 8;

// Variables for calculation
long duration;
int distance;

void setup() {
  // Pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("Distance Meter");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to Trig
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the Echo pin (pulse duration in microseconds)
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters (Speed of sound = 0.0343 cm/us)
  distance = duration * 0.0343 / 2;

  // Display reading on LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance:       "); // Trailing spaces clear old characters

  lcd.setCursor(0, 1);
  if (distance > 400 || distance < 2) {
    lcd.print("Out of Range   ");
  } else {
    lcd.print(distance);
    lcd.print(" cm            ");
  }

  delay(250); // Refresh rate
}
