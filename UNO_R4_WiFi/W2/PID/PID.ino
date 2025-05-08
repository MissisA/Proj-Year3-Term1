// //ล้อซ้าย
// int ENA = 10;
// int IN1 = 6;
// int IN2 = 7;
// //ล้อขวา
// int ENB = 5;
// int IN3 = 9;
// int IN4 = 8;
// //ใช้เก็บค่าที่อ่านได้จากเซ็นเซอร์ TCRT5000L ทั้ง 5 หัว
// int SS_0 = 1;
// int SS_1 = 1;
// int SS_2 = 1;
// int SS_3 = 1;
// int SS_4 = 1;
// //กำหนดค่าเริ่มต้นให้กับการทำ PID
// int Int_Speed = 3000;  // ค่าความเร็วเบื้องต้นของหุ่นยนต์ที่ถูกกำหนดไว้ที่ Duty Cycle ของ PWM 1125 (0 - 4095) 1900 2100 2600 2400
// int moreErr = 0;
// float Kp = 35, Kd = 15;  // ค่0อัตราขยายของ P และ ของ D // 21 26 kd =ค่าเลี้ยว น้อยเลี้ยวน้อย 29 28
// float Err = 0, P = 0, D = 0, PID_Val = 0;
// float Prev_Err = 0;  // Error ในอดีต

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(ENA, OUTPUT);
//   pinMode(ENB, OUTPUT);
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);

//   pinMode(14, INPUT);  //A0
//   pinMode(15, INPUT);  //A1
//   pinMode(16, INPUT);  //A2
//   pinMode(17, INPUT);  //A3
//   pinMode(18, INPUT);  //A4

//   analogWriteResolution(12);  //0-4095
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   Read_Sensors();
//   if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 0)) {
//     stop();
//   } else {
//     PID();
//     MotorCon();
//   }
// }

// void PID() {
//   P = Err;
//   D = Err - Prev_Err;
//   PID_Val = (Kp * P) + (Kd * D);
//   Prev_Err = Err;
// }

// void MotorCon() {
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เดินไปด้านหน้า
//   digitalWrite(IN1, LOW);//มอเตอร์ซ้าย
//   digitalWrite(IN2, HIGH);//มอเตอร์ซ้าย
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
//   //นำค่าที่ได้จากการคำนวณ PID มาทำการเพิ่มหรือรถค่า PWM ที่ล้อซ้ายและล้อขวา
//   int Speed_L = Int_Speed - PID_Val;
//   int Speed_R = Int_Speed + PID_Val;
//   //กำหนดให้ค่า PWM ไม่ควรเกินค่าระหว่าง 0 - 4095
//   constrain(Speed_L, 0, 4095);
//   constrain(Speed_R, 0, 4095);
//   //ขับมอเตอร์ให้เคลื่อนที่ไปตามค่าที่ได้จากการคำนวณ PID
//   analogWrite(ENA, Speed_L);
//   analogWrite(ENB, Speed_R);
// }

// void stop() {
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
// }

// void Read_Sensors() {
//   //ทำการอ่่านค่าเซ็นเซอร์ที่ขาอินพุตแอนาล็อกตั้งแต่ขา A1 - A5 (โดยในที่นี้จะถูกใช้เป็นขาดิจิทัลขา D15 - D19) เข้ามาเก็บไว้ในตัวแปร SS
//   SS_0 = digitalRead(18);
//   SS_1 = digitalRead(17);
//   SS_2 = digitalRead(16);
//   SS_3 = digitalRead(15);
//   SS_4 = digitalRead(14);
//   //กำหนดโหมดสถานะของเซ็นเซอร์ที่ได้จากการอ่านค่าที่เซ็นเซอร์ TCRT5000L ทั้ง 5 หัว
//   if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 0)) {
//     Err = 64 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 0) && (SS_0 == 0)) {
//     Err = 48 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 0) && (SS_0 == 1)) {
//     Err = 32 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 1)) {
//     Err = 16 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = 0;
//   } else if ((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -16 - moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -32 - moreErr;
//   } else if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -48 - moreErr;
//   } else if ((SS_4 == 0) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -64 - moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     if (Err == -64) {
//       Err = -80 - moreErr;
//     } else if (Err == 64) {
//       Err = 80 + moreErr;
//     }
//   }
// }



//ล้อซ้าย
int ENA = 10;
int IN1 = 9;
int IN2 = 8;
//ล้อขวา
int ENB = 5;
int IN3 = 7;
int IN4 = 6;
//ใช้เก็บค่าที่อ่านได้จากเซ็นเซอร์ TCRT5000L ทั้ง 5 หัว
int SS_0 = 1;
int SS_1 = 1;
int SS_2 = 1;
int SS_3 = 1;
int SS_4 = 1;
//กำหนดค่าเริ่มต้นให้กับการทำ PID

int mnSpd = 0;
int mxSpd = 4095;

  int Speed_L = 0;
  int Speed_R = 0 ;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(14, INPUT); //A0
  pinMode(15, INPUT); //A1
  pinMode(16, INPUT); //A2
  pinMode(17, INPUT); //A3
  pinMode(18, INPUT); //A4

  analogWriteResolution(12); //0-4095
}

void loop() {
  Read_Sensors();
  if((SS_4==0)&&(SS_3==0)&&(SS_2==0)&&(SS_1==0)&&(SS_0==0)){
    Speed_L = 0 ;
    Speed_R = 0 ;
  }
  
  // else{
  // PID();
  MotorCon();
  // }
}

// void PID(){
//   P = Err;
//   D = Err - Prev_Err;
//   PID_Val = (Kp*P);
//   Prev_Err = Err;
// }

void MotorCon(){
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //นำค่าที่ได้จากการคำนวณ PID มาทำการเพิ่มหรือรถค่า PWM ที่ล้อซ้ายและล้อขวา

  //กำหนดให้ค่า PWM ไม่ควรเกินค่าระหว่าง 0 - 4095
  constrain(Speed_L, mnSpd , mxSpd);
  constrain(Speed_R, mnSpd , mxSpd);
  //ขับมอเตอร์ให้เคลื่อนที่ไปตามค่าที่ได้จากการคำนวณ PID
  analogWrite(ENA, Speed_R);
  analogWrite(ENB, Speed_L);
}

void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void lb(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENB, 4095);
}

void rb(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  constrain(Speed_L, mnSpd , mxSpd);
  constrain(Speed_R, mnSpd , mxSpd);

  analogWrite(ENA, 4095);
}

void fd(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  constrain(Speed_L, mnSpd , mxSpd);
  constrain(Speed_R, mnSpd , mxSpd);

  analogWrite(ENA, Speed_R);
  analogWrite(ENB, Speed_L);
}

void Read_Sensors(){
  SS_0 = digitalRead(18);
  SS_1 = digitalRead(17);
  SS_2 = digitalRead(16);
  SS_3 = digitalRead(15);
  SS_4 = digitalRead(14);
  int i = 0;
  //01111
  if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==1)&&(SS_0==0)){
    Speed_R = 100 ;
    Speed_L = 4095 ;
    
    i = -1;
  }
  //00111
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==0)&&(SS_0==0)){
    Speed_R = 0;
    Speed_L = 0;
    stop(); // หยุดมอเตอร์
    delay(20);
    Speed_R = 4095;
    Speed_L = 4095;
    fd();
    delay(10);
    Speed_R = 0 ;
    Speed_L = 4095 ;
    
    i = -1;
  }
  //10111
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==0)&&(SS_0==1)){
    Speed_R = 0 ;
    Speed_L = 4095 ;
    
    i = -1;
  }
  //10011
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==0)&&(SS_1==0)&&(SS_0==1)){
    Speed_L = 4095 ;
    Speed_R = 0 ;
    i = -1;
  }
  //11011
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==0)&&(SS_1==1)&&(SS_0==1)){
    Speed_L = 3000 ;
    Speed_R = 3000 ;
    i =2;
  }
  //11001
  else if((SS_4==1)&&(SS_3==0)&&(SS_2==0)&&(SS_1==1)&&(SS_0==1)){
    
    Speed_L = 0 ;
    Speed_R = 4095 ;
    
    i = 1;
  }
  //11101
  else if((SS_4==1)&&(SS_3==0)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    Speed_L = 0 ;
    Speed_R = 4095 ;
    
    i = 1;
  }
  //11100
  else if((SS_4==0)&&(SS_3==0)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    Speed_R = 0;
    Speed_L = 0;
    stop(); // หยุดมอเตอร์
    delay(20);
    Speed_R = 4095;
    Speed_L = 4095;
    fd();
    delay(10);
    Speed_L = 0 ;
    Speed_R = 4095 ;
    i = 1;
  }
  //11110
  else if((SS_4==0)&&(SS_3==1)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    Speed_L = 100 ;
    Speed_R = 4095 ;
    
    i = 1;
  }
  //00001
  else if((SS_4==1)&&(SS_3==0)&&(SS_2==0)&&(SS_1==0)&&(SS_0==0)){
    Speed_R = 0;
    Speed_L = 0;
    stop(); // หยุดมอเตอร์
    delay(20);
    Speed_R = 4095;
    Speed_L = 4095;
    fd();
    delay(10);
    Speed_R = 0 ;
    Speed_L = 4095 ;
    
    i = 1;
  }
  //10000
  else if((SS_4==0)&&(SS_3==0)&&(SS_2==0)&&(SS_1==0)&&(SS_0==1)){
    Speed_R = 0;
    Speed_L = 0;
    stop(); // หยุดมอเตอร์
    delay(20);
    Speed_R = 4095;
    Speed_L = 4095;
    fd();
    delay(10);
    Speed_L = 0 ;
    Speed_R = 4095 ;
    
    i = 1;
  }
  
  //11111
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    if(i == 1|| i == 2){
      Speed_L = 0 ;
      Speed_R = 4095;
      
    }
    if(i == -1){
      Speed_R = 0;
      Speed_L = 4095 ;
    }
    
  }
  
}