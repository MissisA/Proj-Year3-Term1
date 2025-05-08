// //16 การควบคุมหุ่นยนต์ผ่านจอยสติ๊กโมดูล ตอนที่ 1, 17 การควบคุมหุ่นยนต์ผ่านจอยสติ๊กโมดูล ตอนที่ 2

// #include "Arduino_LED_Matrix.h"
// #include "normal.h"
// #include "right.h"
// #include "left.h"
// #include "inv_right.h"
// #include "inv_left.h"
// #include "stop.h"

// ArduinoLEDMatrix matrix;  

// //มอเตอร์ซ้าย
// int ENA=10;
// int IN1=9;
// int IN2=8;
// //มอเตอร์ขวา
// int ENB=5;
// int IN3=7;
// int IN4=6;
// //กำหนดค่าให้กับ Joystick Module
// int joyX = A0;
// int joyY = A1;
// int joyB = 4;
// // ตัวแปรเก็บค่าความเร็วกำหนดค่าเริ่มต้นของความเร็วให้อยู่ที่ 0
// int MotorSpeed_L = 0;
// int MotorSpeed_R = 0;
// // กำหนดค่าดีฟอลต์ให้กับจอยสติ้กที่จุดกึ่งกลางที่ 512
// int joy_pos_Y = 512;
// int joy_pos_X = 512;
// bool joy_button = 0;
// //ใช้ชดเชยการเบี้ยวของการเคลื่อนที่
// int B_L = 0; //ล้อซ้าย
// int B_R = 0; //ล้อขวา

// void setup() {
//   //กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
//   pinMode(ENA, OUTPUT);
//   pinMode(ENB, OUTPUT);
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);
//   pinMode(joyY, INPUT);
//   pinMode(joyX, INPUT);
//   pinMode(joyB, INPUT);
//   // กำหนดค่าเริ่มต้นให้กับมอเตอร์ทั้งด้านซ้ายและด้านขวา (เป็นค่าดีฟอลต์) ให้เป็น 0 ทั้งหมด
//   digitalWrite(ENA, LOW);
//   digitalWrite(ENB, LOW);
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
//   //เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
//   analogWriteResolution(12);

//   // Animation
//   matrix.begin();
//   matrix.play(true);
// }

// void loop() {
//   // อ่านค่าจากจอยสติ้กจาก A0,A1 และ สวิตซ์
//   joy_pos_Y = analogRead(joyY);
//   joy_pos_X = analogRead(joyX); 
//   joy_button = digitalRead(joyB);
//   //เดินหน้า
//   if(joy_pos_Y > 564){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
//     matrix.loadSequence(normal_s);
//     //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
//     digitalWrite(IN1, HIGH);
//     digitalWrite(IN2, LOW);
//     digitalWrite(IN3, HIGH);
//     digitalWrite(IN4, LOW);
//     //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
//     MotorSpeed_L = map(joy_pos_Y,564,1023,0,4095);
//     MotorSpeed_R = map(joy_pos_Y,564,1023,0,4095);
//   }
//   //ถอยหลัง
//   else if (joy_pos_Y < 460){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
//     matrix.loadSequence(normal_s);
//     //กำหนดให้พารามิเตอร์ที่ L298N ถอยหลัง
//     digitalWrite(IN1, LOW);
//     digitalWrite(IN2, HIGH);
//     digitalWrite(IN3, LOW);
//     digitalWrite(IN4, HIGH);
//     // กลับค่าจาก 460 -> 0 เป็น 0 -> 460 แทน
//     joy_pos_Y = (joy_pos_Y - 460)*(-1);
//     //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
//     MotorSpeed_L = map(joy_pos_Y,0,460,0,4095);
//     MotorSpeed_R = map(joy_pos_Y,0,460,0,4095);
//   }
//   else{
//     //สั่งมอเตอร์หยุด
//     MotorSpeed_L = 0;
//     MotorSpeed_R = 0;
//   }
//   // เลี้ยวซ้าย
//   if (joy_pos_X < 460 && joy_button == 0){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
//     matrix.loadSequence(left_s);
//      // กลับค่าจาก 460 -> 0 เป็น 0 -> 460 แทน
//     joy_pos_X = (joy_pos_X - 460)*(-1);
//     //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
//     joy_pos_X = map(joy_pos_X,0,460,0,4095);

//     MotorSpeed_L = MotorSpeed_L - joy_pos_X; //ชลอล้อซ้าย
//     MotorSpeed_R = MotorSpeed_R + joy_pos_X; //เพิ่มความเร็วล้อขวา
//     // เขียนป้องกันค่าเกิน 0 ถึง 4095 กรณีเลี้ยวซ้าย (ล้อซ้ายให้หยุด (0) + ล้อขวาให้วิ่ง(4095))
//     if(MotorSpeed_L < 0){
//       MotorSpeed_L = 0;
//     }
//     if(MotorSpeed_R > 4095){
//       MotorSpeed_R = 4095;
//     }
//   }
//   else if (joy_pos_X > 564 && joy_button == 0){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
//    //เลี้ยวขวา
//    joy_pos_X = map(joy_pos_X,564,1023,0,4095);

//    matrix.loadSequence(right_s);
//    MotorSpeed_L = MotorSpeed_L + joy_pos_X; // เพิ่มความเร็วล้อซ้าย
//    MotorSpeed_R = MotorSpeed_R - joy_pos_X; // ชลอล้อขวา
//    // เขียนป้องกันค่าเกิน 0 ถึง 4095 กรณีเลี้ยวขวา (ล้อซ้ายให้วิ่ง (4095) + ล้อขวาให้หยุด(0)) 
//     if(MotorSpeed_L > 4095){
//       MotorSpeed_L = 4095;
//     }
//     if(MotorSpeed_R < 0){
//       MotorSpeed_R = 0;
//     }
//   }
//   else if (joy_pos_X < 460 && joy_button == 1){ //กรณีที่มีการกดปุ่มแล้วเลี้ยวซ้าย

//     matrix.loadSequence(inv_left_s);
//     //กำหนดให้พารามิเตอร์ที่ L298N ให้หมุนซ้าย
//     digitalWrite(IN1, LOW);
//     digitalWrite(IN2, HIGH);
//     digitalWrite(IN3, HIGH);
//     digitalWrite(IN4, LOW);
//     // กลับค่าจาก 460 -> 0 เป็น 0 -> 460 แทน
//     joy_pos_X = (joy_pos_X - 460)*(-1);
//     //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
//     joy_pos_X = map(joy_pos_X,0,460,0,4095);

//     MotorSpeed_L = joy_pos_X; //เอาค่าใส่ล้อซ้าย
//     MotorSpeed_R = joy_pos_X; //เอาค่าใส่ล้อขวา
//     // เขียนป้องกันค่าเกิน 4095 กรณีหมุนซ้าย (ล้อซ้ายให้วิ่งถอยหลัง(4095) + ล้อขวาให้วิ่งไปหน้า(4095))
//     if(MotorSpeed_L > 4095){
//       MotorSpeed_L = 4095;
//     }
//     if(MotorSpeed_R > 4095){
//       MotorSpeed_R = 4095;
//     }
//   }
//   else if (joy_pos_X > 564 && joy_button == 1){ //กรณีที่มีการกดปุ่มแล้วเลี้ยวขวา

//     matrix.loadSequence(inv_right_s);
//     //กำหนดให้พารามิเตอร์ที่ L298N ให้หมุนขวา
//     digitalWrite(IN1, HIGH);
//     digitalWrite(IN2, LOW);
//     digitalWrite(IN3, LOW);
//     digitalWrite(IN4, HIGH);
//     //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
//     joy_pos_X = map(joy_pos_X,564,1023,0,4095);
//     MotorSpeed_L = joy_pos_X; // เอาค่าใส่ล้อซ้าย
//     MotorSpeed_R = joy_pos_X; // เอาค่าใส่ล้อขวา
//     // เขียนป้องกันค่าเกิน 4095 กรณีหมุนขวา (ล้อซ้ายให้วิ่งไปหน้า(4095) + ล้อขวาให้วิ่งถอยหลัง(4095))
//     if(MotorSpeed_L > 4095){
//       MotorSpeed_L = 4095;
//     }
//     if(MotorSpeed_R > 4095){
//       MotorSpeed_R = 4095;
//     }
//   }
//   // ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050
//   if (MotorSpeed_L<2050){
//     MotorSpeed_L = 0;
//   }
//   if (MotorSpeed_R<2050){
//     MotorSpeed_R = 0;
//   }
//   //คำสั่งขับมอเตอร์ทั้งซ้ายและขวา
//   analogWrite(ENA, MotorSpeed_L - B_L);
//   analogWrite(ENB, MotorSpeed_R - B_R);
// }











#include "Arduino_LED_Matrix.h"
#include "normal.h"
// #include "backward.h"
#include "right.h"
#include "left.h"
#include "inv_right.h"
#include "inv_left.h"
#include "stop.h"

ArduinoLEDMatrix matrix;  

//มอเตอร์ซ้าย
int ENA=10;
int IN1=9;
int IN2=8;
//มอเตอร์ขวา
int ENB=5;
int IN3=7;
int IN4=6;
//กำหนดค่าให้กับ Joystick Module
int joyX = A0;
int joyY = A1;
int joyB = 4;
// ตัวแปรเก็บค่าความเร็วกำหนดค่าเริ่มต้นของความเร็วให้อยู่ที่ 0
int MotorSpeed_L = 0;
int MotorSpeed_R = 0;
// กำหนดค่าดีฟอลต์ให้กับจอยสติ้กที่จุดกึ่งกลางที่ 512
int joy_pos_Y = 512;
int joy_pos_X = 512;
bool joy_button = 0;
//ใช้ชดเชยการเบี้ยวของการเคลื่อนที่
int B_L = 0; //ล้อซ้าย
int B_R = 0; //ล้อขวา
// ย่านต้องห้าม
int L_POINT = 29491;
int H_POINT = 36045;
int E_RES = 65535;
// Animation
unsigned long run_time = 0;
unsigned long prev_time = 0;


void setup() {
  //กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(joyY, INPUT);
  pinMode(joyX, INPUT);
  pinMode(joyB, INPUT);
  // กำหนดค่าเริ่มต้นให้กับมอเตอร์ทั้งด้านซ้ายและด้านขวา (เป็นค่าดีฟอลต์) ให้เป็น 0 ทั้งหมด
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
  analogWriteResolution(12);
  analogReadResolution(16);
  // Animation
  matrix.begin();
  matrix.play(true);
}


// Animation Function
void Animation(){
  run_time = millis();
  if(run_time - prev_time >= 500){
    prev_time = run_time;

    // อ่านค่าจากจอยสติ้กจาก A0,A1 และ สวิตซ์
    joy_pos_Y = analogRead(joyY);
    joy_pos_X = analogRead(joyX); 
    joy_button = digitalRead(joyB);

      //เดินหน้า
    if(joy_pos_Y > H_POINT){
      matrix.loadSequence(normal_s);
    }
    //ถอยหลัง
    else if (joy_pos_Y < L_POINT){
      matrix.loadSequence(normal_s);
    }
    // เลี้ยวซ้าย
    else if(joy_pos_X > H_POINT && joy_button == 1){
      matrix.loadSequence(left_s);
    }
    // เลี้ยวขวา
    else if(joy_pos_X < L_POINT && joy_button == 1){
      matrix.loadSequence(right_s);
    }
    // หมุนซ้าย
    else if(joy_pos_X > H_POINT && joy_button == 0){
      matrix.loadSequence(inv_left_s);
    }
    // หมุนขวา
    else if(joy_pos_X < L_POINT && joy_button == 0){
      matrix.loadSequence(inv_right_s);
    }
    // หยุด
    else{
      matrix.loadSequence(stop_s);
    }
  }
}


// Movement Function
void movement(){
  // อ่านค่าจากจอยสติ้กจาก A0,A1 และ สวิตซ์
  joy_pos_Y = analogRead(joyY);
  joy_pos_X = analogRead(joyX); 
  //joy_button = digitalRead(joyB);

  //เดินหน้า
  if(joy_pos_Y > H_POINT){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
    //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
    
    MotorSpeed_L = map(joy_pos_Y, H_POINT, E_RES, 0, 4095);
    MotorSpeed_R = map(joy_pos_Y, H_POINT, E_RES ,0, 4095);
  }
  //ถอยหลัง
  else if (joy_pos_Y < L_POINT){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
    //กำหนดให้พารามิเตอร์ที่ L298N ถอยหลัง
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    // กลับค่าจาก L_POINT -> 0 เป็น 0 -> L_POINT แทน
    joy_pos_Y = (joy_pos_Y - L_POINT)*(-1);
    //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
    MotorSpeed_L = map(joy_pos_Y, 0, L_POINT, 0, 4095);
    MotorSpeed_R = map(joy_pos_Y, 0, L_POINT, 0, 4095);
  }
  else{
    //สั่งมอเตอร์หยุด
    MotorSpeed_L = 0;
    MotorSpeed_R = 0;
  }
   
  // เลี้ยวซ้าย
  if (joy_pos_X > H_POINT && joy_button == 0){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
     // กลับค่าจาก L_POINT -> 0 เป็น 0 -> L_POINT แทน
    joy_pos_X = map(joy_pos_X, H_POINT, E_RES, 0 ,4095);

    MotorSpeed_L = MotorSpeed_L - joy_pos_X; //ชลอล้อซ้าย
    MotorSpeed_R = MotorSpeed_R + joy_pos_X; //เพิ่มความเร็วล้อขวา
    // เขียนป้องกันค่าเกิน 0 ถึง 4095 กรณีเลี้ยวซ้าย (ล้อซ้ายให้หยุด (0) + ล้อขวาให้วิ่ง(4095))
    if(MotorSpeed_L < 0){
      MotorSpeed_L = 0;
    }
    if(MotorSpeed_R > 3000){
      MotorSpeed_R = 3000;
    }
  }
  //เลี้ยวขวา
  else if (joy_pos_X < L_POINT && joy_button == 0){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
   joy_pos_X = (joy_pos_X - L_POINT)*(-1);
   joy_pos_X = map(joy_pos_X, 0, L_POINT, 0, 4095);
   MotorSpeed_L = MotorSpeed_L + joy_pos_X; // เพิ่มความเร็วล้อซ้าย
   MotorSpeed_R = MotorSpeed_R - joy_pos_X; // ชลอล้อขวา
   // เขียนป้องกันค่าเกิน 0 ถึง 4095 กรณีเลี้ยวขวา (ล้อซ้ายให้วิ่ง (4095) + ล้อขวาให้หยุด(0)) 
    if(MotorSpeed_L > 3000){
      MotorSpeed_L = 3000;
    }
    if(MotorSpeed_R < 0){
      MotorSpeed_R = 0;
    }
  }
  else if (joy_pos_X > H_POINT && joy_button == 1){ //กรณีที่มีการกดปุ่มแล้วเลี้ยวซ้าย
    //กำหนดให้พารามิเตอร์ที่ L298N ให้หมุนซ้าย
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
    joy_pos_X = (joy_pos_X - L_POINT)*(-1);
    joy_pos_X = map(joy_pos_X, H_POINT, E_RES, 0, 4095);

    MotorSpeed_L = joy_pos_X; //เอาค่าใส่ล้อซ้าย
    MotorSpeed_R = joy_pos_X; //เอาค่าใส่ล้อขวา
    // เขียนป้องกันค่าเกิน 4095 กรณีหมุนซ้าย (ล้อซ้ายให้วิ่งถอยหลัง(4095) + ล้อขวาให้วิ่งไปหน้า(4095))
    if(MotorSpeed_L > 4095){
      MotorSpeed_L = 4095;
    }
    if(MotorSpeed_R > 4095){
      MotorSpeed_R = 4095;
    }
  }
  else if (joy_pos_X < L_POINT && joy_button == 1){ //กรณีที่มีการกดปุ่มแล้วเลี้ยวขวา
    //กำหนดให้พารามิเตอร์ที่ L298N ให้หมุนขวา
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
    // joy_pos_X = (joy_pos_X - L_POINT)*(-1);
    joy_pos_X = map(joy_pos_X, 0, L_POINT, 0, 4095);
    MotorSpeed_L = joy_pos_X; // เอาค่าใส่ล้อซ้าย
    MotorSpeed_R = joy_pos_X; // เอาค่าใส่ล้อขวา
    // เขียนป้องกันค่าเกิน 4095 กรณีหมุนขวา (ล้อซ้ายให้วิ่งไปหน้า(4095) + ล้อขวาให้วิ่งถอยหลัง(4095))
    if(MotorSpeed_L > 4095){
      MotorSpeed_L = 4095;
    }
    if(MotorSpeed_R > 4095){
      MotorSpeed_R = 4095;
    }
  }

  // ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050
  if (MotorSpeed_L < 2050){
    MotorSpeed_L = 0;
  }
  if (MotorSpeed_R < 2050){
    MotorSpeed_R = 0;
  }

  //คำสั่งขับมอเตอร์ทั้งซ้ายและขวา
  analogWrite(ENA, MotorSpeed_L - B_L);
  analogWrite(ENB, MotorSpeed_R - B_R);
}


void loop() {
  Animation();
  movement();
}