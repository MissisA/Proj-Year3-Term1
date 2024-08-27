//1 เขียนฟังก์ชั่นการติดดับของ LED ผ่านไมโครคอนโทรเลอร์ Arduino UNO R4 WIFI
// int ledState = LOW;
// void setup() {
//   pinMode(12, OUTPUT);
// }

// void loop() {
//   blinkLED();
//   delay(500);
// }

// void blinkLED(){
//   digitalWrite(12, ledState); //LOW
//   ledState = !ledState; //ledState = HIGH
// }



// //2 เขียนฟังก์ชั่นเพื่อใช้สวิตซ์ควบคุมการติดดับของ LED ผ่านไมโครคอนโทรเลอร์ Arduino UNO R4 WIFI
// int toggleState = LOW; //toggleState เก็บสถานะLED->public variable
// void setup() {
//   pinMode(2, INPUT);
//   pinMode(10, OUTPUT);
// }

// void loop() {
//   toggleLED();
//   delay(100);
// }

// void toggleLED(){
//   if (digitalRead(2) == HIGH){
//     toggleState = HIGH; //กดติด
//   }
//   else {
//     toggleState = LOW; //ปล่อยดับ
//   }
//   digitalWrite(10, toggleState);
// }



// //3 เขียนฟังก์ชั่นเพื่อควบคุมองศาการหมุนของ Servo Motor ผ่านไมโครคอนโทรเลอร์ Arduino UNO R4 WIFI
// /*servo เล็ก DS929HV 
// สายส้ม ขาสญ.รับค่าตัวเลข 0-180 ในการบอกองศาการหมุนของ servo ให้หมุนไปที่เท่าไหร่?>หมุนเป็น-ครึ่งวงกลม
// สายแดง ขาไฟ รองรับ5v, 3.3v
// ตัวแปร servoPos เก็บตน.องศาของ servo
// -servoIncrement = -1 กลับตอนค่า 180 องศา
// +servoIncrement = 1 กลับตอนค่า 0 องศา*/

// #include <Servo.h>
// Servo myServo;
// int servoPos = 0 ; //องศาเริ่มต้น
// int servoIncrement = 1; //กน. step กระโดดทีละ 1 องศา
// void setup() {
//   myServo.attach(9); //ขาสญที่คค.องศาอยู่ขา 9
// }

// void loop() {
//   servoSweep();
//   delay(15);
// }

// void servoSweep(){
//   servoPos = servoPos + servoIncrement;
//   if ((servoPos < 0) || (servoPos > 180)){
//     servoIncrement = -servoIncrement;
//   }
//   myServo.write(servoPos); //drive องศา servo
// }



// //4 ตอนที่ 1 แนะนำฟังก์ชั่น millis(); 
// /*ทำงานแบบ multi-tasking
// นับเริ่มที่ 0-4,294,967,296 (49 days)
// นับ 0-1000 ใช้เวลา 1 s*/

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   unsigned long C; // ประกาศได้แค่ long
//   C = millis();
//   Serial.println(millis());
// }



// //5 ตอนที่ 2 การใช้งานฟังก์ชั่น millis(); เพื่อแทนการทำงาน ฟังก์ชั่น delay();
// /*สั่ง LED ติดดับที่เวลานั้น*/

// int ledState = LOW;
// unsigned long C = 0;//วิ่ง
// unsigned long P = 0;//p=c, วิ่งช้ากว่า 1000
// void setup() {
//   pinMode(12, OUTPUT);
// }

// void loop() {
//   C = millis(); // ใช้แทน Delay
//   blinkLED();
//   // delay(500);
// }

// void blinkLED(){
//   if (C-P >= 1000){ //ค่า C, P = 1000 ปล่อย c วิ่งไปที่ 1500-> 1500-1000= 500 ยังไม่>= 1000 จะกระโดดออก
//     P = C; //ถ้า C-P >= 1000->update p=c
//     ledState = !ledState; //ledState = HIGH
//     digitalWrite(12, ledState); //ขับออกขา 12, LOW
//   }
// }



// //6 ตอนที่ 3 การใช้งานฟังก์ชั่น millis();  ในงาน Multi-tasking แบบ 2 งานควบคู่กัน
// int ledState = LOW;
// int brightness = 0;
// int fadeIncrement = 1;

// unsigned long C = 0;
// unsigned long P_1 = 0;
// unsigned long P_2 = 0;

// void setup() {
//   pinMode(12, OUTPUT);
//   pinMode(11, OUTPUT);
// }

// void loop() {
//   C = millis();
//   blinkLED();
//   fadeLED();
// }

// void blinkLED(){
//   if (C - P_1 >= 1000){
//     P_1 = C;
//     ledState = !ledState;
//     digitalWrite(12, ledState);
//   }
// }

// void fadeLED(){
//   if (C - P_2 >= 5){
//     P_2 = C;
//     brightness = brightness + fadeIncrement; //brightness+1 ไปเรื่อยๆ
//       if ((brightness < 0 || brightness > 255)){
//         fadeIncrement = -fadeIncrement; //กลับเครื่องหมาย
//       }
//   analogWrite(11, brightness); //ขับ brightness
//   }
// }



// /*fade LED ค่อยๆติด-ดับ 
// หรี่ความสว่างของ LED โดยใช้ PWM ผ่านไมโครคอนโทรเลอร์ Arduino UNO R4 WIFI
// 0-255*/

// int brightness = 0;
// int fadeIncrement = 1;
// void setup() {
//   pinMode(11, OUTPUT);
// }

// void loop() {
//   fadeLED();
//   delay(5);
// }

// void fadeLED(){
//   brightness = brightness + fadeIncrement; //brightness+1 ไปเรื่อยๆ
//   if ((brightness < 0 || brightness > 255)){
//     fadeIncrement = -fadeIncrement; //กลับเครื่องหมาย
//   }
//   analogWrite(11, brightness); //ขับ brightness
// }



// //7 ตอนที่ 4 การใช้งานฟังก์ชั่น millis(); ในงาน Multi-tasking แบบ 3 งานควบคู่กัน
// int ledState = LOW;
// int brightness = 0;
// int fadeIncrement = 1;
// int toggleState = LOW; //toggleState เก็บสถานะLED->public variable

// unsigned long C = 0;
// unsigned long P_1 = 0; //blinkLED
// unsigned long P_2 = 0; //fadeLED
// unsigned long P_3 = 0; //toggleLED

// void setup() {
//   pinMode(12, OUTPUT);
//   pinMode(11, OUTPUT);
//   pinMode(2, INPUT);
//   pinMode(10, OUTPUT);
// }

// void loop() {
//   C = millis();
//   blinkLED();
//   fadeLED();
//   toggleLED();
// }

// void blinkLED(){
//   if (C - P_1 >= 1000){
//     P_1 = C;
//     ledState = !ledState;
//     digitalWrite(12, ledState);
//   }
// }

// void fadeLED(){
//   if (C - P_2 >= 5){
//     P_2 = C;
//     brightness = brightness + fadeIncrement; //brightness+1 ไปเรื่อยๆ
//     if ((brightness < 0 || brightness > 255)){
//       fadeIncrement = -fadeIncrement; //กลับเครื่องหมาย
//     }
//     analogWrite(11, brightness); //ขับ brightness
//   }
// }

// void toggleLED(){
//   if (C - P_3 >= 100){
//     P_3 = C;
//     if (digitalRead(2) == HIGH){
//       toggleState = HIGH;
//     }
//     else {
//       toggleState = LOW;
//     }
//     digitalWrite(10, toggleState);
//   }
// }



// // 8 ตอนที่ 5 การใช้งานฟังก์ชั่น millis(); ในงาน Multi-tasking แบบ 4 งานควบคู่กัน

// #include <Servo.h>
// Servo myServo;
// int servoPos = 0 ; //องศาเริ่มต้น
// int servoIncrement = 1; //กน. step กระโดดทีละ 1 องศา
// int ledState = LOW;
// int brightness = 0;
// int fadeIncrement = 1;
// int toggleState = LOW; //toggleState เก็บสถานะLED->public variable

// unsigned long C = 0;
// unsigned long P_1 = 0; //blinkLED
// unsigned long P_2 = 0; //fadeLED
// unsigned long P_3 = 0; //toggleLED
// unsigned long P_4 = 0; //servoSweep

// void setup() {
//   pinMode(12, OUTPUT);
//   pinMode(11, OUTPUT);
//   pinMode(2, INPUT);
//   pinMode(10, OUTPUT);
//   myServo.attach(9); //ขาสญที่คค.องศาอยู่ขา 9
// }

// void loop() {
//   C = millis();
//   blinkLED();
//   fadeLED();
//   toggleLED();
//   servoSweep();
// }

// void blinkLED(){
//   if (C - P_1 >= 1000){
//     P_1 = C;
//     ledState = !ledState;
//     digitalWrite(12, ledState);
//   }
// }

// void fadeLED(){
//   if (C - P_2 >= 5){
//     P_2 = C;
//     brightness = brightness + fadeIncrement; //brightness+1 ไปเรื่อยๆ
//     if ((brightness < 0 || brightness > 255)){
//       fadeIncrement = -fadeIncrement; //กลับเครื่องหมาย
//     }
//     analogWrite(11, brightness); //ขับ brightness
//   }
// }

// void toggleLED(){
//   if (C - P_3 >= 100){
//     P_3 = C;
//     if (digitalRead(2) == HIGH){
//       toggleState = HIGH;
//     }
//     else {
//       toggleState = LOW;
//     }
//     digitalWrite(10, toggleState);
//   }
// }

// void servoSweep(){
//   if (C - P_4 >= 15){
//     P_4 = C;
//     servoPos = servoPos + servoIncrement;
//     if ((servoPos < 0) || (servoPos > 180)){
//       servoIncrement = -servoIncrement;
//     }
//     myServo.write(servoPos); //drive องศา servo
//   }
// }