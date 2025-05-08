//RobotSmartCar EP12+14,EP13,EP15,16+17,19+แสดงหน้าหุ่นยนต์
/*
1. แสดงผลค่า Duty Cycle ที่แคบที่สุดที่ Robot สามารถขับมอเตอร์ได้ โดยทดลองผ่านตัวต้านทานปรับค่าได้ 2 ตัว (ตัวอย่าง EP12 และ EP14) 2 คะแนน
2. แสดงผลการวิ่งของรถหลังจากการทำ PID เพื่อทำให้รถเดินทางเป็นเส้นตรง (EP13) 2 คะแนน
3. การสั่งงานหุ่นยนต์ผ่านโปรแกรมภายในตัวไมโครคอนโทรเลอร์ เดินหน้า ถอยหลัง เลี้ยวซ้าย เลี้ยวขวา หมุนซ้าย และหมุนขวา (EP15) 2 คะแนน
4. การสั่งงานหุ่นยนต์ผ่าน Joystick โมดูล (EP16 และ EP17) 2 คะแนน
5. การแสดงผลสถานะแผง LED ตามการเคลื่อนที่ของโรบอท (EP19) 2 คะแนน
รวมเป็น 10 คะแนน
ข้อที่ 5 การแสดงผล LED ผมขอการแสดงผลเป็นแอนิเมชั่นให้ครบทุกสถานะนะครับ 
(เดินหน้า ถอยหลัง เลี้ยวซ้าย เลี้ยวขวา หมุนซ้าย หมุนขวา และหยุดอยู่กับที่)
ไม่เอาภาพนิ่ง ข้อนี้ไม่ให้โค้ดเฉลยครับ กลุ่มใดทำได้สมควรได้ 10 คะแนนเต็มครับ*/

//EP9-11

// EP12 การหาค่าความแคบที่สุดของ PWM ที่ถูกป้อนให้กับ L298N ที่ทำให้มอเตอร์หุ่นยนต์ไม่ทำงาน
// มอเตอร์ซ้าย
int ENA = 10;
int IN1 = 9;
int IN2 = 8;
//มอเตอร์ขวา
int ENB = 5;
int IN3 = 7;
int IN4 = 6;
//ตัวแปรรักษา PWM จากไมโคร เพื่อควบคุมความเร็วทั้งล้อซ้ายขวา
int MotorSpeed_L = 0;
int MotorSpeed_R = 0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //กาารเพิ่มความละเอียดของ PWM เพื่อใช้ปรับความเร็วมอเตอร์
  // analogWriteResolution(12);//แม่นยำขึ้น, กินพลังงานมากขึ้น
  Serial.begin(9600);
}

void forward(){
  //ฟังก์ชันทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่
  //กำหนดพารามิเตอร์ที่ L298N ให้หุ่นยนต์เดินหน้า สถานะ logic 1010
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  /*กำหนดความเร็วให้มอเตอร์ ค่าตั้งแต่ 0-255(3% 8)->ล้อหมุนที่120(ค่าที่แคบที่สุด), 
  PWMละเอียดขึ้น ค่าตั้งแต่ 0-4095(3% 123)->ล้อหมุนที่2050*/
  MotorSpeed_L = 170;
  MotorSpeed_R = 140;

  if(MotorSpeed_L < 2050){ 
    MotorSpeed_L = 0;
  }
  if(MotorSpeed_R < 2050){
    MotorSpeed_R = 0;
  }
  analogWrite(ENA, MotorSpeed_L);//motor left ,duty cycle 200=4v, PWMละเอียดขึ้น=4095 -> /2=2048
  analogWrite(ENB, MotorSpeed_R);//motor right

}

void loop() {
  forward();
  // กำหนดพารามิเตอร์ที่ L298N ให้หุ่นยนต์เดินหน้า สถานะ logic 1010
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for(int i=0;i<4096;i++){ //PWMละเอียดขึ้น i<4096 ->น้อยกว่า1ค่า
    analogWrite(ENA,i);
    analogWrite(ENB,i);
    Serial.print("PWM ของมอเตอร์: ");
    Serial.println(i);
  }
  delay(250);
}





// //13
// //มอเตอร์ซ้าย
// int ENA = 10;
// int IN1 = 9;
// int IN2 = 8;
// //มอเตอร์ขวา
// int ENB = 5;
// int IN3 = 7;
// int IN4 = 6;
// //ตัวแปรรักษา PWM จากไมโคร เพื่อควบคุมความเร็วทั้งล้อซ้ายขวา
// int MotorSpeed_L = 4000;
// int MotorSpeed_R = 4000;
// //ตัวแปรสำหรับลดความเร็วของล้อในการทำ PID
// int B_L = 170;
// int B_R = 140;

// void setup() {
//   pinMode(ENA, OUTPUT);
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(ENB, OUTPUT);
//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);

//   //กาารเพิ่มความละเอียดของ PWM เพื่อใช้ปรับความเร็วมอเตอร์
//   analogWriteResolution(12);//แม่นยำขึ้น, กินพลังงานมากขึ้น
//   Serial.begin(9600);
// }

// void forward(){
//   //ฟังก์ชันทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่
//   //กำหนดพารามิเตอร์ที่ L298N ให้หุ่นยนต์เดินหน้า สถานะ logic 1010
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
//   /*กำหนดความเร็วให้มอเตอร์ ค่าตั้งแต่ 0-255(3% 8)->ล้อหมุนที่120(ค่าที่แคบที่สุด), 
//   PWMละเอียดขึ้น ค่าตั้งแต่ 0-4095(3% 123)->ล้อหมุนที่2050*/
//   MotorSpeed_L = 4000;
//   MotorSpeed_R = 4000;

//   if(MotorSpeed_L < 2050){
//     MotorSpeed_L = 0;
//   }
//   if(MotorSpeed_R < 2050){
//     MotorSpeed_R = 0;
//   }
//   analogWrite(ENA, MotorSpeed_L - B_L);//motor left ,duty cycle 200=4v, PWMละเอียดขึ้น=4095 -> /2=2048
//   analogWrite(ENB, MotorSpeed_R - B_R);//motor right

// }

// void increase_speed(){
//   //กำหนดพารามิเตอร์ที่ L298N ให้หุ่นยนต์เดินหน้า สถานะ logic 1010
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);

//   for(int i=2050;i<4096;i++){ //PWMละเอียดขึ้น i<4096 ->น้อยกว่า1ค่า
//     analogWrite(ENA, i - B_L);
//     analogWrite(ENB, i - B_R);
//     Serial.print("PWM ของมอเตอร์ : ");
//     Serial.println(i);
//   }
//   for(int i=4095;i>2051;i--){ //PWMละเอียดขึ้น i<4096 ->น้อยกว่า1ค่า
//     analogWrite(ENA, i - B_L);
//     analogWrite(ENB, i - B_R);
//     Serial.print("PWM ของมอเตอร์ : ");
//     Serial.println(i);
//   }
// }

// void loop() {
//   forward();
// }




//14
