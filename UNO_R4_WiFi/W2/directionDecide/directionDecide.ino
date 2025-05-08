// #include <ESP32Servo.h>
#include <Servo.h> 
Servo Myservo;

int TrigPin = 13;
int EchoPin = 12;
float duration, distance;

#define ServoPin 11 // ขา Signal ขับ PWM ของ Servo Motor ออกที่ขา 11 ***
#define Int_wheel_R 2 //กำหนดขาอินพุตที่ต่อจากเซ็นเซอร์ Opto ที่ล้อขวา (ที่ขา INT 0)
#define Int_wheel_L 3 //กำหนดขาอินพุตที่ต่อจากเซ็นเซอร์ Opto ที่ล้อซ้าย (ที่ขา INT 1)
#define PI 3.1415926535897932384626433832795 //กำหนดค่าของ Pi
#define Wheel_Radiant 3.4925 // รัศมีของล้อ

//ล้อขวา
int ENA=10; //กำหนดให้ขาที่ 10 เชื่อมต่อกับขา ENA ของ L298N
int IN1=9; //กำหนดให้ขาที่ 9 เชื่อมต่อกับขา IN1 ของ L298N
int IN2=8; //กำหนดให้ขาที่ 8 เชื่อมต่อกับขา IN2 ของ L298N
//ล้อซ้าย
int ENB=5; //กำหนดให้ขาที่ 5 เชื่อมต่อกับขา ENB ของ L298N
int IN3=7; //กำหนดให้ขาที่ 7 เชื่อมต่อกับขา IN3 ของ L298N
int IN4=6; //กำหนดให้ขาที่ 6 เชื่อมต่อกับขา IN4 ของ L298N

volatile unsigned int noClk_R = 0; //กำหนดตัวแปรที่ใช้นับจำนวน 1 พัลส์จาก Encoder Disk ที่ล้อขวา
volatile unsigned int noClk_L = 0; //กำหนดตัวแปรที่ใช้นับจำนวน 1 พัลส์จาก Encoder Disk ที่ล้อซ้าย

float noSlots = 20.00; //จำนวนช่องว่างของ Encoder Disk บนจานล้อหมุน
float round_distance = 2*PI*Wheel_Radiant; //ระยะทางของล้อหุ่นยนต์ต่อการหมุน 1 รอบ (เส้นรอบวง) หน่วยเป็น ซม. ใช้สูตร 2xPixรัศมีของล้อ
float one_tick = round_distance/noSlots; //ค่าระยะทางการเดินทางของล้อจำนวน 1 พัลส์ที่นับได้จากขา IRQ
float length_wheelbase = 13.5; //ค่าความยาวของฐานล้อ หน่วยเป็นเซ็นติเมตร
float circumference = 2*PI*length_wheelbase; //ระยะทางการเคลื่อนที่ของหุ่นยนต์ในล้อซ้ายหรือล้อขวาในกรณีหมุนครบ 360 องศา Question 1
float TT_noPulse_IRQ = circumference/one_tick; //จำนวนพัลส์ที่นับได้ใน ISR ที่ล้อซ้ายหรือล้อขวาในกรณีที่หุ่นยนต์เลี้ยวครบ 360 องศา Question 2
float anglePerIRQ = 360/TT_noPulse_IRQ; //ค่าองศาที่เกิดขึ้นของการเลี้ยวต่อการนับจำนวนพัลส์ 1 พัลส์ใน ISR Question 3


float distance_R = 0; //ตัวแปรที่ใช้เก็บระยะทางการเดินทางของล้อขวาหน่วยเป็นเซ็นติเมตร
float distance_L = 0; //ตัวแปรที่ใช้เก็บระยะทางการเดินทางของล้อซ้ายหน่วยเป็นเซ็นติเมตร

void ISR_count_R(){ // นับจำนวนพัลส์ที่ผ่านช่องว่างของ Encoder Disk บนจานล้อหมุนที่ล้อขวา
  noClk_R = noClk_R + 1; //เพิ่มค่าจำนวนของตัวแปรที่ใช้นับ IRQ ที่ล้อขวาไป 1
}

void ISR_count_L(){ // นับจำนวนพัลส์ที่ผ่านช่องว่างของ Encoder Disk บนจานล้อหมุนที่ล้อซ้าย
  noClk_L = noClk_L + 1; //เพิ่มค่าจำนวนของตัวแปรที่ใช้นับ IRQ ที่ล้อซ้ายไป 1
}
// ฟังก์ชั่นนี้จะทำหน้าที่สั่งให้หุ่นยนต์ทำการวัดระยะห่างของวัตถุที่อยู่ด้านหน้าของเซ็นเซอร์อัลตราโซนิก HC-SR04 ออกมาเป็นเซ็นติเมตร มาเก็บไว้ในตัวแปร distance ***
void Get_Distance(){ // ***
  digitalWrite(TrigPin, LOW);   // เคลียร์ค่าที่ขา Trig ของ HC-SR04 ***
  delayMicroseconds(2);   // ดีเลย์ไป 2 ไมโครวินาที ***
  digitalWrite(TrigPin, HIGH);  // สั่งให้ขา Trig ทำการส่งคลื่นอัลตราโซนิก ความถี่ 40 KHz จำนวน 8 ลูก ออกไปที่ปล้องของ Transmit ***
  delayMicroseconds(10); // ดีเลย์ไป 10 ไมโครวินาที ***
  duration = pulseIn(EchoPin, HIGH);        // รับคลื่นสะท้อนที่รับกลับมาที่ขา Echo ***
  distance = (duration*.0343)/2;            // คำนวณหาระยะห่างของวัตถุที่อยู่ด้านหน้าของเซ็นเซอร์หรือสิ่งกีดขวางที่อยู่ด้านหน้าหน่วยเป็น เซ็นติเมตร ***
  delay(10); //ดีเลย์ไป 10 มิลลิวินาที ***
}
//ฟังก์ชั่นนี้จะทำการแปลงระยะทางการเดินของหุ่นยนต์จากหน่วยเซ็นติเมตรเป็นจำนวนพัลส์ที่ต้องนับใน ISR สำหรับดักค่า IRQ ในล้อซ้ายและล้อขวา ใช้ในกรณีเดินหน้าและถอยหลัง
int CM_To_noClk(float IP_cm){
  float TT_noClk_B = IP_cm/one_tick;
  int TT_noClk = (int) TT_noClk_B;
  return TT_noClk;
}
//ฟังก์ชั่นนี้จะทำการแปลงความเร็วของหุ่นยนต์จากหน่วยเซ็นติเมตร/วินาทีเป็นค่า Duty Cycle ของ PWM เพื่อใช้ป้อนให้กับขา ENA และ ENB ของ L298N
int SP_To_PWM(float IP_sp){
  int TT_PWM = map(IP_sp,0,70,0,4095); //แม็พค่าความเร็วสูงสุดของหุ่นยนต์ ในที่นี้คือ 70 เซ็นติเมตรต่อวินาทีให้มีค่าระหว่าง 0-4095
  return TT_PWM;
}
//ฟังก์ชั่นนี้จะทำการแปลงค่าองศาการเลี้ยวของหุ่นยนต์ไปเป็นจำนวนพัลส์ที่ต้องนับใน ISR สำหรับดักค่า IRQ ในล้อซ้ายหรือล้อขวา ใช้ในกรณีเลี้ยวซ้ายและเลี้ยวขวา
int DGT_To_noClk(float IP_dg){
  float TT_noClk_D = IP_dg*(1/anglePerIRQ);
  int TT_noClk = (int) TT_noClk_D;
  return TT_noClk;
}
//ฟังก์ชั่นนี้จะทำการแปลงค่าองศาการหมุนของหุ่นยนต์ไปเป็นจำนวนพัลส์ที่ต้องนับใน ISR สำหรับดักค่า IRQ ในล้อซ้ายและล้อขวา ใช้ในกรณีหมุนซ้ายและหมุนขวา
int DGR_To_noClk(float IP_dgr){
  float TT_noClk_DR = IP_dgr*(1/(2*anglePerIRQ));
  int TT_noClk = (int) TT_noClk_DR;
  return TT_noClk;
}
//ตัวแปรรับค่า PWM จากไมโครฯ เพื่อควบคุมความเร็วทั้งล้อซ้ายและขวา
int MotorSpeed_L = 4000;
int MotorSpeed_R = 4000;
//ตัวแปรสำหรับลดความเร็วของล้อในการทำ PID
int B_L = 0;
int B_R = 1570;


void forward(){
  //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //กำหนดความเร็วให้กับมอเตอร์ 
  
  if(MotorSpeed_L < 1800){
    MotorSpeed_L = 0;
  }
  if(MotorSpeed_R < 1800){
    MotorSpeed_R = 0;
  }
  analogWrite(ENA, MotorSpeed_L - B_L); //มอเตอร์ซ้าย
  analogWrite(ENB, MotorSpeed_R - B_R); //มอเตอร์ขวา
}

void backward(){
  //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  //กำหนดความเร็วให้กับมอเตอร์ 
  
  if(MotorSpeed_L < 1800){
    MotorSpeed_L = 0;
  }
  if(MotorSpeed_R < 1800){
    MotorSpeed_R = 0;
  }
  analogWrite(ENA, MotorSpeed_L - B_L); //มอเตอร์ซ้าย
  analogWrite(ENB, MotorSpeed_R - B_R); //มอเตอร์ขวา
}

//ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการหมุนขวา อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการหมุนมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการหมุนมีหน่วยเป็นองศา
void spin_right(float CMpS_speed, float DG_spin){
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการหมุนขวา (ล้อซ้ายเดินหน้าล้อขวาถอยหลัง)
  digitalWrite(IN1, HIGH); //ล้อซ้าย
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); //ล้อขวา
  digitalWrite(IN4, HIGH);
  //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
  noClk_R = 0;
  noClk_L = 0;
  //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
  int PWM_speed = SP_To_PWM(CMpS_speed);
  //ทำการแปลงค่าองศาการหมุนให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อขวา
  int Pulse_angle = DGR_To_noClk(DG_spin);
  //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อซ้ายว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
  while (Pulse_angle > noClk_L){
    //ในกรณีล้อซ้ายและขวา
    if(Pulse_angle > noClk_L){
      analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
      analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
    }
    else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
      analogWrite(ENA, 0);
      analogWrite(ENB, 0); 
    }
  }
  //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
  if (PWM_speed < 2050){
    PWM_speed = 0;
  }
  //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
  noClk_R = 0;
  noClk_L = 0;
}

//ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการหมุนซ้าย อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการหมุนมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการหมุนมีหน่วยเป็นองศา
void spin_left(float CMpS_speed, float DG_spin){
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการหมุนซ้าย (ล้อซ้ายถอยหลังล้อขวาเดินหน้า)
  digitalWrite(IN1, LOW); //ล้อซ้าย
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); //ล้อขวา
  digitalWrite(IN4, LOW);
  //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
  noClk_R = 0;
  noClk_L = 0;
  //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
  int PWM_speed = SP_To_PWM(CMpS_speed);
  //ทำการแปลงค่าองศาการหมุนให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อขวา
  int Pulse_angle = DGR_To_noClk(DG_spin);
  //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อขวาว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
  while (Pulse_angle > noClk_R){
    //ในกรณีล้อซ้ายและขวา
    if(Pulse_angle > noClk_R){
      analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
      analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
    }
    else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
      analogWrite(ENA, 0);
      analogWrite(ENB, 0); 
    }
  }
  //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
  if (PWM_speed < 2050){
    PWM_speed = 0;
  }
  //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
  noClk_R = 0;
  noClk_L = 0;
}

//ฟังก์ชั่นนี้จะทำให้หุ่นยนต์หยุดเดิน
void stop(){
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เพื่อให้หุ่นยนต์หยุดเดิน
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void wallCheck(){
  Get_Distance();
  int dis[] = {0,0,0};
  char dir[] = {'f','l','r'};

  Myservo.write(100);
  delay(500);
  Get_Distance();
  delay(100);
  dis[0] = distance;
  Serial.print("Front: ");
  Serial.println(distance);

  Myservo.write(180);
  delay(500);
  spin_right(50,20);
  Get_Distance();
  delay(100);
  dis[1] = distance;
  Serial.print("Left: ");
  Serial.println(distance);
  delay(250);
  spin_left(50,20);
  delay(250);

  Myservo.write(0);
  delay(500);
  Get_Distance();
  delay(100);
  dis[2] = distance;
  Serial.print("Right: ");
  Serial.println(distance);

  Myservo.write(100);
  delay(200);  

  int tempDis = 0;
  char tempDir = ' ';

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 2; j++){
      // Compare distances
      if(dis[j] < dis[j+1]){
          // Swap the distances if they are out of order
          tempDis = dis[j];
          dis[j] = dis[j+1];
          dis[j+1] = tempDis;

          // Swap corresponding directions
          tempDir = dir[j];
          dir[j] = dir[j+1];
          dir[j+1] = tempDir;
      }
    }
  }

  Serial.print("Direction: ");
  Serial.println(dir[0]);

  if(dir[0] == 'f'){
    backward();
    delay(100);
    stop();
    delay(100);
    // forward();
    // delay(50);
  }
  else if(dir[0] == 'l'){
    spin_right(50,80);
    stop();
    delay(100);
  }
  else if(dir[0] == 'r'){
    spin_left(50,90);
    stop();
    delay(350);
  }
  stop();
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TrigPin, OUTPUT); // กำหนดให้ขา TrigPin (ขาที่ 13) เป็นเอาต์พุต***
  pinMode(EchoPin, INPUT); // กำหนดให้ขา EchoPin (ขาที่ 12) เป็นอินพุต ***
  //ประกาศเพื่อเรียกใช้งานพอร์ต UART เพื่อส่งค่ากลับไปยัง Serial Monitor ***
  Serial.begin(9600); // ***
  //กำหนดค่าในการทำ Hardware IRQ
  attachInterrupt(digitalPinToInterrupt(Int_wheel_R), ISR_count_R, RISING); // กำหนดพารามิเตอร์สำหรับ HW IRQ ให้กับล้อขวาเพื่อนับจำนวนพัลส์ที่ขอบขาขึ้น
  attachInterrupt(digitalPinToInterrupt(Int_wheel_L), ISR_count_L, RISING); // กำหนดพารามิเตอร์สำหรับ HW IRQ ให้กับล้อซ้ายเพื่อนับจำนวนพัลส์ที่ขอบขาขึ้น
  
  analogWriteResolution(12); //เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
  
  Myservo.attach(ServoPin); //ขาดาต้าของเซอร์โวต่อที่ขา 11 ***
  Myservo.write(90); //กำหนดให้ค่าเริ่มต้นขององศาการขยับของเซอร์โวอยู่ตรงกลาง คือ 90 องศา (ชดเชยการ Jitter ไป 10 องศา) ***
  delay(500); // ทำการดีเลย์รอให้เซอร์โวมอเตอร์ปัดแกนไปที่ 90 องศาไปครึ่งวินาที ***
}

void loop() {
  Get_Distance();
  if(distance > 45){
    forward();
    // Serial.print("Distance: ");
    // Serial.println(distance);
    // delay(200);
    // stop();
    // // wallCheck();
    // delay(500);
  }
  else{
    stop();
    wallCheck();
  }

}
