//13 ปรับจูน

//มอเตอร์ซ้าย
int ENA=10;
int IN1=9;
int IN2=8;
//มอเตอร์ขวา
int ENB=5;
int IN3=7;
int IN4=6;
//ตัวแปรรับค่า PWM จากไมโครฯ เพื่อควบคุมความเร็วทั้งล้อซ้ายและขวา
int MotorSpeed_L = 0;
int MotorSpeed_R = 0;
//ตัวแปรสำหรับลดความเร็วของล้อในการทำ PID
int B_L = 300;
int B_R = 1500;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //การเพิ่มความละเอียดของ PWM เพื่อใช้ปรับความเร็วของมอเตอร์
  analogWriteResolution(12); //มีค่าตั้งแต่ 0 - 4095
  Serial.begin(9600);
}

void forward(){
  //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //กำหนดความเร็วให้กับมอเตอร์ 
  MotorSpeed_L = 4000;
  MotorSpeed_R = 4000;
  
  if(MotorSpeed_L < 1800){
    MotorSpeed_L = 0;
  }
  if(MotorSpeed_R < 1800){
    MotorSpeed_R = 0;
  }
  analogWrite(ENA, MotorSpeed_L - B_L); //มอเตอร์ซ้าย
  analogWrite(ENB, MotorSpeed_R - B_R); //มอเตอร์ขวา
}

void increase_speed(){
  //ฟังก์ชั่นนี้จะทำการเพิ่มค่าความเร็วของรถขึ้นไปเรีื่อย ๆ
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  for(int i =2050;i<4096;i++){
    analogWrite(ENA,i - B_L);
    analogWrite(ENB,i - B_R);
  }
  for(int i =4095;i>2051;i--){
    analogWrite(ENA,i - B_L);
    analogWrite(ENB,i - B_R);
  }
}

void loop() {
  forward();
}
