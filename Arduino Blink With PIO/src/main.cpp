#include <Arduino.h>

unsigned short int LEDPin = 8;

void setup() {
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  digitalWrite(LEDPin, HIGH);
  delay(400);
  digitalWrite(LEDPin, LOW);
  delay(400);
}