//ล้อซ้าย
int ENA = 10;
int IN1 = 6;
int IN2 = 7;
//ล้อขวา
int ENB = 5;
int IN3 = 9;
int IN4 = 8;
//ใช้เก็บค่าที่อ่านได้จากเซ็นเซอร์ TCRT5000L ทั้ง 5 หัวa
int SS_0 = 1;
int SS_1 = 1;
int SS_2 = 1;
int SS_3 = 1;
int SS_4 = 1;
//กำหนดค่าเริ่มต้นให้กับการทำ PID
int Int_Speed = 4095;  // ค่าความเร็วเบื้องต้นของหุ่นยนต์ที่ถูกกำหนดไว้ที่ Duty Cycle ของ PWM 1125 (0 - 4095)
int moreErr = 16;
float Kp = 50, Kd = Kp * 2.5;  // ค่าอัตราขยายของ P และ ของ D
float Err = 0, P = 0, D = 0, PID_Val = 0;
float Prev_Err = 0;  // Error ในอดีต

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(14, INPUT);  //A0
  pinMode(15, INPUT);  //A1
  pinMode(16, INPUT);  //A2
  pinMode(17, INPUT);  //A3
  pinMode(18, INPUT);  //A4

  analogWriteResolution(12);  //0-4095

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Sensors();
  if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 0)) {
    stop();
  } else {
    PID();
    MotorCon();
  }
}

void PID() {
  P = Err;
  D = Err - Prev_Err;
  PID_Val = (Kp * P) + (Kd * D);
  Prev_Err = Err;
}

void MotorCon() {
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //นำค่าที่ได้จากการคำนวณ PID มาทำการเพิ่มหรือรถค่า PWM ที่ล้อซ้ายและล้อขวา
  int Speed_L = Int_Speed - PID_Val;
  int Speed_R = Int_Speed + PID_Val;
  //กำหนดให้ค่า PWM ไม่ควรเกินค่าระหว่าง 0 - 4095
  constrain(Speed_L, 0, 4095);
  constrain(Speed_R, 0, 4095);
  //ขับมอเตอร์ให้เคลื่อนที่ไปตามค่าที่ได้จากการคำนวณ PID
  analogWrite(ENA, Speed_L);
  analogWrite(ENB, Speed_R);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Read_Sensors() {
  // ทำการอ่่านค่าเซ็นเซอร์ที่ขาอินพุตแอนาล็อกตั้งแต่ขา A1 - A5 
  SS_0 = digitalRead(19);
  SS_1 = digitalRead(18);
  SS_2 = digitalRead(17);
  SS_3 = digitalRead(16);
  SS_4 = digitalRead(15);

  int count = SS_0 + SS_1 + SS_2 + SS_3 + SS_4;

  if (count == 1 || count == 2 || count == 3) {
    // Logic for turning to the other direction
    Err = -64 - moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 0)) {
    Err = 64 + moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 0) && (SS_0 == 0)) {
    Err = 64 + moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 0)) {
    Err = -64 - moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 1)) {
    Err = 32 + moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 0) && (SS_0 == 1)) {
    Err = 32 + moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 1)) {
    Err = 16 + moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
    Err = 0;
  } else if ((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
    Err = -16 - moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
    Err = -32 - moreErr;
  } else if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
    Err = -32 - moreErr;
  } else if ((SS_4 == 0) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
    Err = -64 - moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
    Err = -64 - moreErr;
  } else if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
    Err = 64 + moreErr;
  } else if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 1)) {
    Err = -64 - moreErr;
  } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
    if (Err == -64) {
      Err = -80 - moreErr;
    } else if (Err == 64) {
      Err = 80 + moreErr;
    }
  }
}

//   if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 0)) {
//     Err = 64 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 0) && (SS_0 == 0)) {
//     Err = 64 + moreErr;
//   } else if (((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 0))) {
//     Err = 64 + moreErr;
//   } else if (((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 0))) {
//     Err = 64 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 0) && (SS_0 == 1)) {
//     Err = 32 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 1)) {
//     Err = 16 + moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = 0;
//   }



//   else if ((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -16 - moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 0) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -32 - moreErr;
//   } else if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -64 - moreErr;
//   } else if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -64 - moreErr;
//   } else if ((SS_4 == 0) && (SS_3 == 0) && (SS_2 == 0) && (SS_1 == 0) && (SS_0 == 1)) {
//     Err = -64 - moreErr;
//   } else if ((SS_4 == 0) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     Err = -64 - moreErr;
//   } else if ((SS_4 == 1) && (SS_3 == 1) && (SS_2 == 1) && (SS_1 == 1) && (SS_0 == 1)) {
//     if (Err == -64 - moreErr) {
//       Err = -80 - moreErr;
//     } else if (Err == 64 + moreErr) {
//       Err = 80 + moreErr;
//     }
//   }
// }
