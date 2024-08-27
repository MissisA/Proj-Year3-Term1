// //Arduino UNO R4 8x12 Matrix
// //1/7
// #include "Arduino_LED_Matrix.h"
// ArduinoLEDMatrix matrix;

// void setup() {
//   matrix.begin();
// }

// uint8_t frame[8][12] = {
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//   };

// void loop() {
//   frame[0][0]=1;//ติดที่ตน.นี้ 0, 0 
//   frame[7][11]=1;//ดับที่ตน.สุดท้าย 7, 11 
//   frame[7][0]=1;//ติดที่ตน.นี้ 0, 0 
//   frame[0][11]=1;//ดับที่ตน.สุดท้าย 7, 11 

//   matrix.renderBitmap(frame, 8, 12);
//   delay(1000);
  
//   frame[0][0]=0;//ดับที่ตน.นี้ 0, 0
//   frame[7][11]=0;//ติดที่ตน. 7, 11
//   frame[7][0]=0;//ติดที่ตน.นี้ 0, 0 
//   frame[0][11]=0;//ดับที่ตน.สุดท้าย 7, 11 
//   matrix.renderBitmap(frame, 8, 12);
//   delay(1000);
// }

// //2/7

// #include "Arduino_LED_Matrix.h"
// ArduinoLEDMatrix matrix;

// void setup() {
//   matrix.begin();
// }

// uint8_t frame[8][12] = {
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//   };

// void loop() {
//   int i, j;
//   for (i=0; i<12; i++){
//     for (j=0; j<8; j++){
//       frame[i][j]=1;
//       matrix.renderBitmap(frame, 8, 12);
//       delay(250);

//       frame[i][j]=0;
//       matrix.renderBitmap(frame, 8, 12);
//       delay(250);

//     }
//   }
// }

//3/7
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();
}

uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};


void loop() {
  //กระพริบสลับกันซ้ายขวา
  w_le();//
  re();
  mnt();
  ns();
  matrix.renderBitmap(frame, 8, 12);
  delay(500);

  le();
  w_re();//
  matrix.renderBitmap(frame, 8, 12);
  delay(500);
}

void le(){ //left eye
  frame[1][3]=1;
  frame[1][4]=1;
  frame[2][3]=1;
  frame[2][4]=1;
}

void re(){//right eye
  frame[1][8]=1;
  frame[1][9]=1;
  frame[2][8]=1;
  frame[2][9]=1;
}

void mnt(){//ปาก
  frame[5][3]=1;
  frame[5][9]=1;
  frame[6][3]=1;
  frame[6][4]=1;
  frame[6][5]=1;
  frame[6][6]=1;
  frame[6][7]=1;
  frame[6][8]=1;
  frame[6][9]=1;
}

void ns(){//noseจมูก
  frame[3][6]=1;
}

void w_le(){//wing leftกระพริบตาซ้าย
  frame[1][3]=0;
  frame[1][4]=0;
  frame[2][3]=1;
  frame[2][4]=1;
}

void w_re(){//wing กระพริบตาซ้าย
  frame[1][8]=0;
  frame[1][9]=0;
  frame[2][8]=1;
  frame[2][9]=1;
}

//4/7 play animation
//https://ledmatrix-editor.arduino.cc/?_gl=1*plyih2*_gcl_au*MTQ2ODc0NDMxNC4xNzE4NDY0NTEz*FPAU*MTQ2ODc0NDMxNC4xNzE4NDY0NTEz*_ga*MTk3ODkwNDYxLjE3MDk2OTAxNjk.*_ga_NEXN8H46L5*MTcyMTcwOTgzOC40LjEuMTcyMTcwOTkwMS4wLjAuMTU3NzQ5MzQ2OQ..*_fplc*cyUyRkZ0VW14VUklMkJFNFJsQlpub0JLOEtCbEdhYzNwN2VFRU1panRvSVRYemFkTDRSNDRWTThJbXFpek8xWUppdkExamJ0dnFrYVpkNnJnMGZ6V1QlMkZTZEdYdDNCS0RYR0olMkJES1lWYTZkQU13ZiUyRldWelE4OCUyQjRydFpRRkRjVHpRJTNEJTNE


//5/7 test_animation

//6/7 play_animation_test
