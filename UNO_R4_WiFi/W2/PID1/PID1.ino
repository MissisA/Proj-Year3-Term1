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
int Int_Speed = 2500; // ค่าความเร็วเบื้องต้นของหุ่นยนต์ที่ถูกกำหนดไว้ที่ Duty Cycle ของ PWM 1125 (0 - 4095)
int Kp = 25, Kd = Kp*2; // ค่าอัตราขยายของ P และ ของ D
float Err = 0, P = 0, D= 0, PID_Val = 0;
float Prev_Err = 0; // Error ในอดีต

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(15, INPUT); //A0
  pinMode(16, INPUT); //A1
  pinMode(17, INPUT); //A2
  pinMode(18, INPUT); //A3
  pinMode(19, INPUT); //A4

  analogWriteResolution(12); //0-4095
}

void loop() {
  Read_Sensors();
  if((SS_4==0)&&(SS_3==0)&&(SS_2==0)&&(SS_1==0)&&(SS_0==0)){
    stop();
  }
  else{
    PID();
  MotorCon();
  }
  // put your main code here, to run repeatedly:
  
  
}

void PID(){
  P = Err;
  D = Err - Prev_Err;
  PID_Val = (Kp*P)+(Kd*D);
  Prev_Err = Err;
}

void MotorCon(){
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //นำค่าที่ได้จากการคำนวณ PID มาทำการเพิ่มหรือรถค่า PWM ที่ล้อซ้ายและล้อขวา
  int Speed_L = Int_Speed - PID_Val; //2350
  int Speed_R = Int_Speed + PID_Val; //2600
  //กำหนดให้ค่า PWM ไม่ควรเกินค่าระหว่าง 0 - 4095
  constrain(Speed_L, 0 , 4095);
  constrain(Speed_R, 0 , 4095);
  //ขับมอเตอร์ให้เคลื่อนที่ไปตามค่าที่ได้จากการคำนวณ PID
  analogWrite(ENA, Speed_L);
  analogWrite(ENB, Speed_R);
}

void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Read_Sensors(){
  //ทำการอ่่านค่าเซ็นเซอร์ที่ขาอินพุตแอนาล็อกตั้งแต่ขา A0 - A4 (โดยในที่นี้จะถูกใช้เป็นขาดิจิทัลขา D14 - D18) เข้ามาเก็บไว้ในตัวแปร SS
  SS_0 = digitalRead(18);
  SS_1 = digitalRead(17);
  SS_2 = digitalRead(16);
  SS_3 = digitalRead(15);
  SS_4 = digitalRead(14);
  //กำหนดโหมดสถานะของเซ็นเซอร์ที่ได้จากการอ่านค่าที่เซ็นเซอร์ TCRT5000L ทั้ง 5 หัว
  if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==1)&&(SS_0==0)){
    Err = 56;
  }
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==0)&&(SS_0==0)){
    Err = 42;
  }
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==0)&&(SS_0==1)){
    Err = 32;
  }
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==0)&&(SS_1==0)&&(SS_0==1)){
    Err = 16;
  }
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==0)&&(SS_1==1)&&(SS_0==1)){
    Err = 0;
  }
  else if((SS_4==1)&&(SS_3==0)&&(SS_2==0)&&(SS_1==1)&&(SS_0==1)){
    Err = -16;
  }
  else if((SS_4==1)&&(SS_3==0)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    Err = -32;
  }
  else if((SS_4==0)&&(SS_3==0)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    Err = -42;
  }
  else if((SS_4==0)&&(SS_3==1)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    Err = -56;
  }
  else if((SS_4==1)&&(SS_3==1)&&(SS_2==1)&&(SS_1==1)&&(SS_0==1)){
    if(Err == -64){
      Err = -80;
    }
  }
  else{
    Err = 80;
  }
}