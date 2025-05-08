#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library
#include "animation.h"     
ArduinoLEDMatrix matrix;

void setup() {
  pinMode(13, OUTPUT);
  matrix.loadSequence(animation);
  matrix.begin();
  
  matrix.play(true);
}

void loop() {
  int d_time = 1000;
  digitalWrite(13, 1);
  delay(d_time);
  digitalWrite(13, 0);
  delay(d_time);
}