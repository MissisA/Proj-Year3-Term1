#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library
#include "animation.h"     
ArduinoLEDMatrix matrix;


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  // you can also load frames at runtime, without stopping the refresh
  matrix.loadSequence(animation);
  matrix.begin();
  // turn on autoscroll to avoid calling next() to show the next frame; the paramenter is in milliseconds
  // matrix.autoscroll(300);
  matrix.play(true);
}

void loop() {
  int d_time = 1000;
  digitalWrite(13, 1);
  delay(d_time);
  digitalWrite(13, 0);
  delay(d_time);
}