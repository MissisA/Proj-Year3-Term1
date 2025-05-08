//19 การใช้งานแผง LED ของ Arduino UNO R4 WiFi เพื่อแสดงสถานะของหุ่นยนต์

#include "Arduino_LED_Matrix.h"
#include "normal.h"
#include "right.h"
#include "left.h"
#include "inv_right.h"
#include "inv_left.h"
#include "stop.h"

ArduinoLEDMatrix matrix; 

volatile int playn = 0;
volatile int Led_finalstate = 0;
volatile unsigned int prev_time = 0;
volatile unsigned int prev_time1 = 0;
volatile unsigned int prev_time2 = 0;
volatile unsigned int prev_time4 = 0;
volatile unsigned int prev_time5 = 0;
volatile unsigned int prev_time6 = 0;
volatile unsigned int prev_time7 = 0;

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
int L_POINT = 1843;
int H_POINT = 2253;
int E_RES = 4095;

// Animation
unsigned long run_time = 0;
unsigned long prev_time = 0;


void setup() {
  //กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  matrix.begin();
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(joyY, INPUT);
  pinMode(joyX, INPUT);
  pinMode(joyB, INPUT);
  // กำหนดค่าเริ่มต้นให้กับมอเตอร์ทั้งด้านซ้ายและด้านขวา (เป็นค่าDefault) ให้เป็น 0 ทั้งหมด
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
void loop(){
  run_time = millis();//แทนDelay
  if(run_time - prev_time >= 500){
    prev_time = run_time; //update prev_time = run_time
    playn = 1;
    // อ่านค่าจากจอยสติ้กจาก A0,A1 และ สวิตซ์
    joy_pos_Y = analogRead(joyY);
    joy_pos_X = analogRead(joyX);
    joy_button = digitalRead(joyB);

    Serial.println(joy_button);
    // display();
    //เดินหน้า
    if(joy_pos_Y > H_POINT){
      playn = 1;
      matrix.loadSequence(normal_s);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      //เอาค่าที่ได้มาแปลงให้อยู่ในรูปของอินพุตที่เป็น PWM (0 - 4095) แล้วส่งค่าไปยังมอเตอร์ซ้ายและมอเตอร์ขวา
      MotorSpeed_L = map(joy_pos_Y, H_POINT, E_RES, 0, 4095);
      MotorSpeed_R = map(joy_pos_Y, H_POINT, E_RES ,0, 4095);
    }
    //ถอยหลัง
    else if (joy_pos_Y < L_POINT){
      playn = 2;
      matrix.loadSequence(normal_s);
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
    // เลี้ยวซ้าย
    else if(joy_pos_X > H_POINT && joy_button == 0){
      matrix.loadSequence(left_s);
    }
    // เลี้ยวขวา
    else if(joy_pos_X < L_POINT && joy_button == 0){
      matrix.loadSequence(right_s);
    }
    // หมุนซ้าย
    else if(joy_pos_X > H_POINT && joy_button == 1){
      matrix.loadSequence(inv_left_s);
    }
    // หมุนขวา
    else if(joy_pos_X < L_POINT && joy_button == 1){
      matrix.loadSequence(inv_right_s);
    }
    // หยุด
    else{
      playn =0;
      matrix.loadSequence(stop_s);
      //สั่งมอเตอร์หยุด
      MotorSpeed_L = 0;
      MotorSpeed_R = 0;
      }
  // เลี้ยวซ้าย
  if (joy_pos_X > H_POINT && joy_button == 0){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  // กลับค่าจาก L_POINT -> 0 เป็น 0 -> L_POINT แทน
    joy_pos_X = map(joy_pos_X, H_POINT, E_RES, 0 ,4095);

    MotorSpeed_L = MotorSpeed_L - joy_pos_X; //ชลอล้อซ้าย
    MotorSpeed_R = MotorSpeed_R + joy_pos_X; //เพิ่มความเร็วล้อขวา
    // เขียนป้องกันค่าเกิน 0 ถึง 4095 กรณีเลี้ยวซ้าย (ล้อซ้ายให้หยุด (0) + ล้อขวาให้วิ่ง(4095))
    if(MotorSpeed_L < 0){
      MotorSpeed_L = 0;
    }
    if(MotorSpeed_R > 4095){
      MotorSpeed_R = 4095;
    }
  }
    //เลี้ยวขวา
    else if (joy_pos_X < L_POINT && joy_button == 0){ // หลบค่าที่อยู่ในช่วงของย่านต้องห้ามของจอยสติ้ก
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    joy_pos_X = (joy_pos_X - L_POINT)*(-1);
    joy_pos_X = map(joy_pos_X, 0, L_POINT, 0, 4095);
    MotorSpeed_L = MotorSpeed_L + joy_pos_X; // เพิ่มความเร็วล้อซ้าย
    MotorSpeed_R = MotorSpeed_R - joy_pos_X; // ชลอล้อขวา
    // เขียนป้องกันค่าเกิน 0 ถึง 4095 กรณีเลี้ยวขวา (ล้อซ้ายให้วิ่ง (4095) + ล้อขวาให้หยุด(0)) 
      if(MotorSpeed_L > 4095){
        MotorSpeed_L = 4095;
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
      joy_pos_X = (joy_pos_X - L_POINT)*(-1);
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
    if (MotorSpeed_L < 1980){
      MotorSpeed_L = 0;
    }
    if (MotorSpeed_R < 1980){
      MotorSpeed_R = 0;
    }

  //คำสั่งขับมอเตอร์ทั้งซ้ายและขวา
  analogWrite(ENA, MotorSpeed_L - B_L);
  analogWrite(ENB, MotorSpeed_R - B_R);
  }

}

void display(){
  if(playn == 1){
    if(Led_finalstate != 1){
      matrix.play(false);
      Led_finalstate = 1;
    }
     if (millis() - prev_time1 >= 1500) 
            {
            matrix.play(false);
            matrix.loadSequence(st5);
            matrix.play(true);
            prev_time1 = millis();  // อัปเดต prev_time หลังจากทำงานเสร็จ
              }
     else if (millis() - prev_time1 >= 1200)
            {
          matrix.play(false);
          matrix.loadSequence(st4);
          matrix.play(true);
          // อัปเดต prev_time หลังจากทำงานเสร็จ
             }
    else if (millis() - prev_time1 >= 900) 
            {
            matrix.play(false);
            matrix.loadSequence(st3);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time1 >= 600) 
            {
            matrix.play(false);
            matrix.loadSequence(st2);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time1 >= 300) 
            {
            matrix.play(false);
            matrix.loadSequence(st1);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }

    
  }else if(playn == 2){
         if(Led_finalstate != 2)
         {
            matrix.play(false);
            Led_finalstate = 2;
         }
         if (millis() - prev_time2 >= 1500) 
            {
            matrix.play(false);
            matrix.loadSequence(bk5);
            matrix.play(true);
            prev_time2 = millis();  // อัปเดต prev_time หลังจากทำงานเสร็จ
              }
     else if (millis() - prev_time2 >= 1200)
            {
          matrix.play(false);
          matrix.loadSequence(bk4);
          matrix.play(true);
          // อัปเดต prev_time หลังจากทำงานเสร็จ
             }
    else if (millis() - prev_time2 >= 900) 
            {
            matrix.play(false);
            matrix.loadSequence(bk3);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time2 >= 600) 
            {
            matrix.play(false);
            matrix.loadSequence(bk2);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time2 >= 300) 
            {
            matrix.play(false);
            matrix.loadSequence(bk1);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    
    

  }else if(playn == 4){
        if(Led_finalstate != 4)
         {
            matrix.play(false);
            Led_finalstate = 4;
         }
         if (millis() - prev_time4 >= 1500) 
            {
            matrix.play(false);
            matrix.loadSequence(left5);
            matrix.play(true);
            prev_time4 = millis();  // อัปเดต prev_time หลังจากทำงานเสร็จ
              }
     else if (millis() - prev_time4 >= 1200)
            {
          matrix.play(false);
          matrix.loadSequence(left4);
          matrix.play(true);
          // อัปเดต prev_time หลังจากทำงานเสร็จ
             }
    else if (millis() - prev_time4 >= 900) 
            {
            matrix.play(false);
            matrix.loadSequence(left3);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time4 >= 600) 
            {
            matrix.play(false);
            matrix.loadSequence(left2);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time4 >= 300) 
            {
            matrix.play(false);
            matrix.loadSequence(left1);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }

  }else if(playn == 5){
        if(Led_finalstate != 5)
         {
            matrix.play(false);
            Led_finalstate = 5;
         }
         if (millis() - prev_time5 >= 1500) 
            {
            matrix.play(false);
            matrix.loadSequence(right5);
            matrix.play(true);
            prev_time5 = millis();  // อัปเดต prev_time หลังจากทำงานเสร็จ
              }
     else if (millis() - prev_time5 >= 1200)
            {
          matrix.play(false);
          matrix.loadSequence(right4);
          matrix.play(true);
          // อัปเดต prev_time หลังจากทำงานเสร็จ
             }
    else if (millis() - prev_time5 >= 900) 
            {
            matrix.play(false);
            matrix.loadSequence(right3);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time5 >= 600) 
            {
            matrix.play(false);
            matrix.loadSequence(right2);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time5 >= 300) 
            {
            matrix.play(false);
            matrix.loadSequence(right1);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }

  }else if(playn == 6){
        if(Led_finalstate != 6)
         {
            matrix.play(false);
            Led_finalstate = 6;
         }
         if (millis() - prev_time6 >= 1500) 
            {
            matrix.play(false);
            matrix.loadSequence(rollle5);
            matrix.play(true);
            prev_time6 = millis();  // อัปเดต prev_time หลังจากทำงานเสร็จ
              }
     else if (millis() - prev_time6 >= 1200)
            {
          matrix.play(false);
          matrix.loadSequence(rollle4);
          matrix.play(true);
          // อัปเดต prev_time หลังจากทำงานเสร็จ
             }
    else if (millis() - prev_time6 >= 900) 
            {
            matrix.play(false);
            matrix.loadSequence(rollle3);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time6 >= 600) 
            {
            matrix.play(false);
            matrix.loadSequence(rollle2);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time6 >= 300) 
            {
            matrix.play(false);
            matrix.loadSequence(rollle1);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }

  }else 
  if(playn == 7){
        if(Led_finalstate != 7)
         {
            matrix.play(false);
            Led_finalstate = 7;
         }
         if (millis() - prev_time7 >= 1500) 
            {
            matrix.play(false);
            matrix.loadSequence(rollri5);
            matrix.play(true);
            prev_time7 = millis();  // อัปเดต prev_time หลังจากทำงานเสร็จ
              }
     else if (millis() - prev_time7 >= 1200)
            {
          matrix.play(false);
          matrix.loadSequence(rollri4);
          matrix.play(true);
          // อัปเดต prev_time หลังจากทำงานเสร็จ
             }
    else if (millis() - prev_time7 >= 900) 
            {
            matrix.play(false);
            matrix.loadSequence(rollri3);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time7 >= 600) 
            {
            matrix.play(false);
            matrix.loadSequence(rollri2);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }
    else if (millis() - prev_time6 >= 300) 
            {
            matrix.play(false);
            matrix.loadSequence(rollri1);
            matrix.play(true);
              // อัปเดต prev_time หลังจากทำงานเสร็จ
            }

  }else
      {
        if(Led_finalstate != 0){
          matrix.play(false);
          Led_finalstate = 0;
        }
      if (millis() - prev_time >= 1500) {
            matrix.play(false);
            matrix.loadSequence(normal3);
            matrix.play(true);
            prev_time = millis();  // อัปเดต prev_time หลังจากทำงานเสร็จ
        }
  }