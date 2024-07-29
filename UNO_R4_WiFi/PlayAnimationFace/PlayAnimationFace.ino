//Design IN : https://ledmatrix-editor.arduino.cc/?_gl=1*plyih2*_gcl_au*MTQ2ODc0NDMxNC4xNzE4NDY0NTEz*FPAU*MTQ2ODc0NDMxNC4xNzE4NDY0NTEz*_ga*MTk3ODkwNDYxLjE3MDk2OTAxNjk.*_ga_NEXN8H46L5*MTcyMTcwOTgzOC40LjEuMTcyMTcwOTkwMS4wLjAuMTU3NzQ5MzQ2OQ..*_fplc*cyUyRkZ0VW14VUklMkJFNFJsQlpub0JLOEtCbEdhYzNwN2VFRU1panRvSVRYemFkTDRSNDRWTThJbXFpek8xWUppdkExamJ0dnFrYVpkNnJnMGZ6V1QlMkZTZEdYdDNCS0RYR0olMkJES1lWYTZkQU13ZiUyRldWelE4OCUyQjRydFpRRkRjVHpRJTNEJTNE

#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library
#include "normal.h"
#include "left.h"
#include "right.h"
#include "stop.h"
#include "inv_left.h"
#include "inv_right.h"

ArduinoLEDMatrix matrix;  

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.play(true);
}

/*---------------------------------------------------------*/

void loop() {
  normal();
  delay(1000);

  left();
  delay(1000);

  right();
  delay(1000);

  stop();
  delay(1000);

  inv_left();
  delay(1000);

  inv_right();
  delay(1000);
}

/*---------------------------------------------------------*/

void normal() {
  matrix.loadSequence(normal_s);
}

/*---------------------------------------------------------*/

void left() {
  matrix.loadSequence(left_s);
}

/*---------------------------------------------------------*/

void right(){
  matrix.loadSequence(right_s);
}

/*---------------------------------------------------------*/

void stop() {
  matrix.loadSequence(stop_s);
}

/*---------------------------------------------------------*/

void inv_left() {
  matrix.loadSequence(inv_left_s);
}

/*---------------------------------------------------------*/

void inv_right() {
  matrix.loadSequence(inv_right_s);
}