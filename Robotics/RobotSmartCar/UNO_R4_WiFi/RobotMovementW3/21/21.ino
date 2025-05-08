//21 การหาระยะทางการเคลื่อนที่ของหุ่นยนต์

#define Int_wheel_R 2 
#define Int_wheel_L 3

//มอเตอร์ซ้าย
int ENA=10;
int IN1=9;
int IN2=8;
//มอเตอร์ขวา
int ENB=5;
int IN3=7;
int IN4=6;

volatile float noSlots = 20.00;
volatile float round_distance = 22.00;

volatile unsigned int noClk_R = 0;
volatile unsigned int noClk_L = 0;

void ISR_count_R() {
  noClk_R = noClk_R + 1;

}

void ISR_count_L() {
  noClk_L = noClk_L + 1;
  
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

}

void setup() {
  //กำหนดให้ขาต่าง ๆ เป็นอินพุตและเอาต์พุต
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(Int_wheel_R), ISR_count_R, RISING);
  attachInterrupt(digitalPinToInterrupt(Int_wheel_L), ISR_count_L, RISING);

  Serial.begin(9600);

}

void loop() {
  forward();
  Serial.println("ระยะทางการหมุนล้อขวา: ");
  Serial.println((noClk_R/noSlots)*round_distance);
  
  Serial.println("ระยะทางการหมุนล้อซ้าย: ");
  Serial.println((noClk_L/noSlots)*round_distance);
}



//22

//23