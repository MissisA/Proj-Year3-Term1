//15การสั่งงานให้หุ่นยนต์ ถอยหลัง เลี้ยวซ้าย เลี้ยวขวา หมุนซ้าย หมุนขวา และหยุด

#include "Arduino_LED_Matrix.h"
#include "normal.h"
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

// // Animation
// unsigned long run_time = 0;
// unsigned long prev_time = 0;

//ใช้ชดเชยการเบี้ยวของการเคลื่อนที่
int B_L = 0; //ล้อซ้าย
int B_R = 0; //ล้อขวา

void setup() {
  //กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
  analogWriteResolution(12);

  // Animation
  matrix.begin();
  matrix.play(true);
}

void forward(){
  matrix.loadSequence(normal_s);
  // delay(3000);
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เคลื่อนที่ไปข้างหน้าด้วยความเร็วคงที่
  //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายและขวาที่ 4000 โดยค่าความเร็วจะมีค่าได้ตั้งแต่ 0 ไปจนถึง 4095
  analogWrite(ENA, 4000-B_L);
  analogWrite(ENB, 4000-B_R);
}

void backward(){
  matrix.loadSequence(normal_s);
  // delay(3000);
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เคลื่อนที่ไปข้างหลังด้วยความเร็วคงที่
  //กำหนดให้พารามิเตอร์ที่ L298N ถอยหลัง
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายและขวาที่ 4000 โดยค่าความเร็วจะมีค่าได้ตั้งแต่ 0 ไปจนถึง 4095
  analogWrite(ENA, 4000-B_L);
  analogWrite(ENB, 4000-B_R);
}

void forward_left(){
  matrix.loadSequence(left_s);
  // delay(3000);
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวซ้าย
  //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายหยุดและขวาที่ค่าความเร็ว 4000 
  analogWrite(ENA, 0);
  analogWrite(ENB, 4000-B_R);
}

// void backward_left(){
//   // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวซ้ายแบบถอยหลัง
//   //กำหนดให้พารามิเตอร์ที่ L298N ให้ถอยหลัง
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
//   // ใส่ความเร็วให้กับมอเตอร์ซ้ายหยุดและขวาที่ค่าความเร็ว 4000 
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 4000-B_R);
// }

void forward_right(){
  matrix.loadSequence(right_s);
  // delay(3000);
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวขวา
  //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายที่ค่าความเร็ว 4000 และขวาหยุด
  analogWrite(ENA, 4000-B_L);
  analogWrite(ENB, 0);
}

// void backward_right(){
//   // ฟังก์ชั่นนี้จะให้หุ่นยนต์ถอยหลังเลี้ยวขวา
//   //กำหนดให้พารามิเตอร์ที่ L298N ให้ถอยหลัง
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
//   // ใส่ความเร็วให้กับมอเตอร์ซ้ายที่ค่าความเร็ว 4000 และขวาหยุด
//   analogWrite(ENA, 4000-B_L);
//   analogWrite(ENB, 0);
// }

void around_right(){
  matrix.loadSequence(inv_right_s);
  // delay(3000);
  //ฟังก์ชั่นนี้จะให้หุ่นยนต์หมุนรอบตัวเองไปทางขวา
  //กำหนดให้พารามิเตอร์ที่ L298N หมุนขวา
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายและขวาที่ค่าความเร็ว 4000
  analogWrite(ENA, 4000-B_L);
  analogWrite(ENB, 4000-B_R);
}

void around_left(){
  matrix.loadSequence(inv_left_s);
  // delay(3000);
  //ฟังก์ชั่นนี้จะให้หุ่นยนต์หมุนรอบตัวเองไปทางซ้าย
  //กำหนดให้พารามิเตอร์ที่ L298N หมุนซ้าย
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายและขวาที่ค่าความเร็ว 4000
  analogWrite(ENA, 4000 - B_L);
  analogWrite(ENB, 4000 - B_R);
}

void stop(){
  matrix.loadSequence(stop_s);
  // delay(3000);
  //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์หยุดเดิน คือการสั่งให้มอเตอร์ซ้ายและขวาหยุด
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  forward();
  delay(3000);
  backward();
  delay(3000);
  // forward_left();
  // delay(3000);
  // backward_left();
  // delay(3000);
  // forward_right();
  // delay(3000);
  // backward_right();
  // delay(3000);
  around_left();
  delay(3000);
  around_right();
  delay(3000);
}
