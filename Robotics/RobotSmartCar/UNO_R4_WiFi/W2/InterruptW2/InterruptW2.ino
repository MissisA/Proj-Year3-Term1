// //ไม่มีลายเซ็น 9 Episode 1 เริ่มต้นกับการใช้งาน Hardware Interrupts กับ Arduino UNO R4 WiFi
// /*Interrupt is ขัดจังหวะการทำงาน */

// volatile bool a = false;

// void setup() {
//   a = true;
//   attachInterrupt((2), ISR, FALLING); //((ขา), function interrupt, mode)
// }

// void loop() {
//   a = false;
// }

// void ISR() { //function ที่กน.ไว้เมื่อเกิดการ Interrupt อย่างด่วนที่สุด
//   a = true;
// }



// //10 Episode 2 เคสตัวอย่างเครื่องจักรสำหรับคัดแยกสินค้าโดยไม่ได้ใช้วิธีการ Interrupts แก้วงจร !!!**
// //ปห. คือ ต้องรอให้หมุนสุด ถึงจะกดปุ่ม>แล้วจะหยุดทำงาน
// #include <Servo.h>

// #define SERVO_PIN 9
// #define LED_RED 5
// #define LED_GREEN 6
// #define BUTTON_PIN 2

// Servo servo_1; //libraly servo.h
// int pos = 180;//position

// // volatile bool a = false;

// void setup() {
//   Serial.begin(9600);

//   pinMode(SERVO_PIN, OUTPUT);
//   pinMode(LED_RED, OUTPUT);
//   pinMode(LED_GREEN, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT);

//   servo_1.attach(SERVO_PIN);
//   servo_1.write(pos);

//   delay(1000);
// }

// void loop() {
//   //ปัดขวา
//   for(pos=180 ; pos>90 ; pos--){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }
//   //ปัดซ้าย
//   for(pos=90 ; pos<180 ; pos++){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }
//   //เมื่อมีการกดปุ่ม
//   if (digitalRead(BUTTON_PIN)==LOW){
//     digitalWrite(LED_RED, HIGH);
//     digitalWrite(LED_GREEN, LOW);
//     delay(3000);
//   }
// }



// //11 Episode 3 การใช้งาน Hardware Interrupts เบื้องต้น ในโหมดการทำงาน LOW
// /*สั่งให้ เมื่อกดสวิตซ์ ให้ servo หยุดทันที*/

// #include <Servo.h>

// #define SERVO_PIN 9
// #define LED_RED 5
// #define LED_GREEN 6
// #define BUTTON_PIN 2

// Servo servo_1; //libraly servo.h
// int pos = 180;//position

// void setup() {
//   Serial.begin(9600);

//   pinMode(SERVO_PIN, OUTPUT);
//   pinMode(LED_RED, OUTPUT);
//   pinMode(LED_GREEN, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT);

//   servo_1.attach(SERVO_PIN);
//   servo_1.write(pos);

//   delay(1000);

//   attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,LOW);
//   //pull-up , LOW = '0' เมื่อกดสวิตซ์โดดไฟทำงานฟังก์ชัน Lemon

// }

// void Lemon() { //mode LOW ทำงานที่นี่ กดสวิตซ์
//   digitalWrite(LED_RED, HIGH);
//   digitalWrite(LED_GREEN, LOW);
// }

// void loop() { //mode HIGH กลับมาทำงานที่นี่ ปล่อยสวิตซ์
//   //ปัดขวา
//   for(pos=180;pos>90;pos--){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }
//   //ปัดซ้าย
//   for(pos=90;pos<180;pos++){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }

// }


// //12 Episode 4 การใช้งาน Hardware Interrupts ในโหมดการทำงาน FALLING, RISING และ CHANGE
// /*เกิดการเบาซิ่งของสวิตซ์ได้ทุก mode ยกเว้น LOW
// FALLING, RISING ใช้ในงานจับองศาการหมุนมอเตอร์ของหุ่นยนต์*/
// #include <Servo.h>

// #define SERVO_PIN 9
// #define LED_RED 5
// #define LED_GREEN 6
// #define BUTTON_PIN 2

// Servo servo_1; //libraly servo.h
// int pos = 180;//position

// // volatile bool a = false;

// void setup() {
//   Serial.begin(9600);

//   pinMode(SERVO_PIN, OUTPUT);
//   pinMode(LED_RED, OUTPUT);
//   pinMode(LED_GREEN, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT);

//   servo_1.attach(SERVO_PIN);
//   servo_1.write(pos);

//   // attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,LOW); //pull-up , LOW = '0' เมื่อกดสวิตซ์โดด ไปทำงานฟังก์ชัน Lemon
//   attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,FALLING); //pull-up , FALLING ปล่อยสวิตซ์ โดดไปทำงานฟังก์ชัน Lemon (HIGH->LOW)
//   // attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,RISING); //pull-up , RISING กดสวิตซ์ โดดไปทำงานฟังก์ชัน Lemon (LOW->HIGH)
//   // attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,CHANGE); //pull-up , CHANGE(FALLING+RISING) กดสวิตซ์หรือปล่อยสวิตซ์ก็ติด โดดไปทำงานฟังก์ชัน Lemon (HIGH->LOW || LOW->HIGH)

//   delay(1000);
// }

// void Lemon() { //mode LOW ทำงานที่นี่ กดสวิตซ์
//   digitalWrite(LED_RED, HIGH);
//   digitalWrite(LED_GREEN, LOW);
// }

// void loop() { //mode HIGH กลับมาทำงานที่นี่ ปล่อยสวิตซ์
//   //ปัดขวา
//   for(pos=180 ; pos>90 ; pos--){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }
//   //ปัดซ้าย
//   for(pos=90 ; pos<180 ; pos++){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }
//   // //เมื่อมีการกดปุ่ม
//   // if (digitalRead(BUTTON_PIN)==LOW){
//   //   digitalWrite(LED_RED, HIGH);
//   //   digitalWrite(LED_GREEN, LOW);
//   //   delay(3000);
//   // }
// }





// //13 Episode 5 การประกาศตัวแปรแบบ Global Variable ด้วยคำสั่ง Volatile เพื่อใช้งานใน Interrupts
// // /*ไม่ว่าจะอยู่องศาไหนก็ตามจะกลับมาที่ 180 เสมอ เมื่อปล่อย*/

// #include <Servo.h>

// #define SERVO_PIN 9
// #define LED_RED 5
// #define LED_GREEN 6
// #define BUTTON_PIN 2

// Servo servo_1; //libraly servo.h
// // int pos = 180;//position

// volatile int pos = 180; //ประกาศตัวแปรให้ทำงานร่วมกับฟังก์ชันอื่นๆ

// void setup() {
//   Serial.begin(9600);

//   pinMode(SERVO_PIN, OUTPUT);
//   pinMode(LED_RED, OUTPUT);
//   pinMode(LED_GREEN, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT);

//   servo_1.attach(SERVO_PIN);
//   servo_1.write(pos);

//   attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,LOW); //pull-up , LOW = '0' เมื่อกดสวิตซ์โดด ไปทำงานฟังก์ชัน Lemon

//   delay(1000);
// }

// void Lemon() { //mode LOW ทำงานที่นี่ กดสวิตซ์
//   pos = 180; //กลับไปที่องศา 180 เสมอ
//   digitalWrite(LED_RED, HIGH);
//   digitalWrite(LED_GREEN, LOW);
// }

// void loop() { //mode HIGH กลับมาทำงานที่นี่ ปล่อยสวิตซ์
//   //ปัดขวา
//   for(pos=180 ; pos>90 ; pos--){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }
//   //ปัดซ้าย
//   for(pos=90 ; pos<180 ; pos++){
//     servo_1.write(pos);
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
//     delay(40);
//   }
// }




//14 Episode 6 การ Debounce สวิตซ์เพื่อใช้งาน Interrupts โดยใช้ฟังก์ชั่น millis();
#include <Servo.h>

#define SERVO_PIN 9
#define LED_RED 5
#define LED_GREEN 6
#define BUTTON_PIN 2

Servo servo_1; //libraly servo.h
// int pos = 180;//position

volatile int pos = 180; //ประกาศตัวแปรให้ทำงานร่วมกับฟังก์ชันอื่นๆ
volatile int prev_time = 0; //Debounce เพิ่ม delay

void setup() {
  Serial.begin(9600);

  pinMode(SERVO_PIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  servo_1.attach(SERVO_PIN);
  servo_1.write(pos);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,LOW); //pull-up , LOW = '0' เมื่อกดสวิตซ์โดด ไปทำงานฟังก์ชัน Lemon
  // attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,FALLING); //pull-up , FALLING ปล่อยสวิตซ์ โดดไปทำงานฟังก์ชัน Lemon (HIGH->LOW)
  // attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,RISING); //pull-up , RISING กดสวิตซ์ โดดไปทำงานฟังก์ชัน Lemon (LOW->HIGH)
  // attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),Lemon,CHANGE); //pull-up , CHANGE(FALLING+RISING) กดสวิตซ์หรือปล่อยสวิตซ์ก็ติด โดดไปทำงานฟังก์ชัน Lemon (HIGH->LOW || LOW->HIGH)

  delay(1000);
}

void Lemon() { //mode LOW ทำงานที่นี่ กดสวิตซ์
  // delay(250); NO
  if(millis() - prev_time >= 250) {
    prev_time = millis();
    pos = 180;
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
  }
}

void loop() { //mode HIGH กลับมาทำงานที่นี่ ปล่อยสวิตซ์
  //ปัดขวา
  for(pos=180 ; pos>90 ; pos--){
    servo_1.write(pos);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
    delay(40);
  }
  //ปัดซ้าย
  for(pos=90 ; pos<180 ; pos++){
    servo_1.write(pos);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
    delay(40);
  }
}