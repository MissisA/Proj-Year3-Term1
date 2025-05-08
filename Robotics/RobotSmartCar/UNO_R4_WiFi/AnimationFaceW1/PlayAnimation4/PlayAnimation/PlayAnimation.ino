/*
  Play Animation

  Sketch shows animation defined in animation.h

  See the full documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix
*/

//https://ledmatrix-editor.arduino.cc/?_gl=1*plyih2*_gcl_au*MTQ2ODc0NDMxNC4xNzE4NDY0NTEz*FPAU*MTQ2ODc0NDMxNC4xNzE4NDY0NTEz*_ga*MTk3ODkwNDYxLjE3MDk2OTAxNjk.*_ga_NEXN8H46L5*MTcyMTcwOTgzOC40LjEuMTcyMTcwOTkwMS4wLjAuMTU3NzQ5MzQ2OQ..*_fplc*cyUyRkZ0VW14VUklMkJFNFJsQlpub0JLOEtCbEdhYzNwN2VFRU1panRvSVRYemFkTDRSNDRWTThJbXFpek8xWUppdkExamJ0dnFrYVpkNnJnMGZ6V1QlMkZTZEdYdDNCS0RYR0olMkJES1lWYTZkQU13ZiUyRldWelE4OCUyQjRydFpRRkRjVHpRJTNEJTNE

#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library
#include "animation.h"            //Include animation.h header file
#include ""

// Create an instance of the ArduinoLEDMatrix class
ArduinoLEDMatrix matrix;  

void setup() {
  Serial.begin(115200);
  // you can also load frames at runtime, without stopping the refresh
  matrix.loadSequence(animation);
  matrix.begin();
  // turn on autoscroll to avoid calling next() to show the next frame; the paramenter is in milliseconds
  // matrix.autoscroll(300);
  matrix.play(true);
}

void loop() {
  delay(500);
  Serial.println(millis());
}
