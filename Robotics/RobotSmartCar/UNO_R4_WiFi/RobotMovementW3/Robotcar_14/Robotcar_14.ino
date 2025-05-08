//14 การควบคุมความเร็วหุ่นยนต์ (PWM) ผ่านตัวต้านทานปรับค่าได้

//มอเตอร์ซ้าย
int ENA=10;
int IN1=9;
int IN2=8;
//มอเตอร์ขวา
int ENB=5;
int IN3=7;
int IN4=6;

// ตัวแปรเก็บค่าความเร็วกำหนดค่าเริ่มต้นของความเร็วให้อยู่ที่ 0
int MotorSpeed_L = 0;
int MotorSpeed_R = 0;
//ใช้ชดเชยการเบี้ยวของการเคลื่อนที่
int B_L = 0; //ล้อซ้าย
int B_R = 0; //ล้อขวา

void setup() {
  //กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  analogReadResolution(8);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  //เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
  //analogWriteResolution(12);
  //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
}

void loop() {
  
  //อ่านค่าจากตัวต้านทานปรับค่าได้ทั้งสองข้างทั้ง A0 และ A1 เอามาเก็บไว้ในตัวแปร
  MotorSpeed_L = analogRead(A0);
  MotorSpeed_R = analogRead(A1);
  //ทำการแม็พค่าที่ได้รับที่ A0 และ A1 จาก 0 - 1023 ไปเป็น 0 - 4095
  int ML = map(MotorSpeed_L, 0, 255, 0, 4095);
  int MR = map(MotorSpeed_R, 0, 255, 0, 4095);
  // เขียนโปรแกรมป้องกันค่ามอเตอร์อยู่ในความเร็วที่ทำให้มอเตอร์เสียหาย โดยปกติแล้วจะอยู่ในช่วง 0 ถึง 2050
  
  // ส่งค่าความเร็วไปยังขา ENA และ ENB
  analogWrite(ENA, ML);
  analogWrite(ENB, MR);
  Serial.print("PWM L: ");
  Serial.println(ML);
  Serial.print("PWM R: ");
  Serial.println(MR);
}
