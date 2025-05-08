//EP3.2
// void setup() {
//   pinMode(2, OUTPUT);

// }

// void loop() {
//   digitalWrite(2, HIGH); //มากที่สุด
//   delay(1000);
//   digitalWrite(2, LOW); //ต่ำที่สุด
//   delay(1000);

// }

//EP3.3 ***********************************************************************
// void setup() {
//   pinMode(2, OUTPUT);
//   pinMode(13, OUTPUT);
//   pinMode(14, OUTPUT);
//   pinMode(15, OUTPUT);
//   pinMode(16, OUTPUT);

// }

// void loop() {
//   digitalWrite(2, 1); //มากที่สุด
//   digitalWrite(13, LOW);
//   digitalWrite(14, HIGH);
//   digitalWrite(15, HIGH);
//   digitalWrite(16, HIGH);
//   delay(1000); //1 SEC
//   digitalWrite(2, 0); //ต่ำที่สุด
//   digitalWrite(13, HIGH);
//   digitalWrite(14, LOW);
//   digitalWrite(15, LOW);
//   digitalWrite(16, LOW);
//   delay(1000);

// }

//EP3.4 ***********************************************************************
// void setup() {
//   pinMode(2, OUTPUT);
//   pinMode(13, OUTPUT);
//   int d_time = 250;
//   digitalWrite(14, 0);
//   delay(500);
//   digitalWrite(14, 1);
//   delay(500);
//   digitalWrite(15, 0);
//   delay(500);
//   digitalWrite(15, 1);
//   delay(500);
//   digitalWrite(16, 0);
//   delay(500);
//   digitalWrite(16, 1);
//   delay(500);
// }

// void loop() {
//   digitalWrite(2, 1);
//   digitalWrite(13, LOW);
//   delay(1000);
//   digitalWrite(2, 0);
//   digitalWrite(13, HIGH);
//   delay(1000);
// }

//EP3.5 ***********************************************************************
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  int d_time = 500;
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(d_time);

  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(d_time);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  delay(d_time);

   digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(d_time);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  delay(d_time);

  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(d_time);
}
//EP3.5แต่ง ***********************************************************************
// void setup() {
//   pinMode(2, OUTPUT);
//   pinMode(3, OUTPUT);
//   pinMode(4, OUTPUT);
//   pinMode(5, OUTPUT);
// }

// void loop() {
//   int d_time = 100;
//   digitalWrite(2, HIGH);
//   digitalWrite(3, HIGH);
//   digitalWrite(4, LOW);
//   digitalWrite(5, HIGH);
//   delay(d_time);

//   digitalWrite(2, LOW);
//   digitalWrite(3, HIGH);
//   digitalWrite(4, LOW);
//   digitalWrite(5, HIGH);
//   delay(d_time);

//   digitalWrite(2, HIGH);
//   digitalWrite(3, HIGH);
//   digitalWrite(4, HIGH);
//   digitalWrite(5, LOW);
//   delay(d_time);

//    digitalWrite(2, LOW);
//   digitalWrite(3, LOW);
//   digitalWrite(4, HIGH);
//   digitalWrite(5, HIGH);
//   delay(d_time);

//   digitalWrite(2, LOW);
//   digitalWrite(3, HIGH);
//   digitalWrite(4, LOW);
//   digitalWrite(5, LOW);
//   delay(d_time);

//   digitalWrite(2, HIGH);
//   digitalWrite(3, HIGH);
//   digitalWrite(4, HIGH);
//   digitalWrite(5, HIGH);
//   delay(d_time);
// }

// EP3.6 ***********************************************************************
// void setup() {
//   Serial.begin(9600);
//   pinMode(2, OUTPUT);
//   pinMode(3, OUTPUT);
//   pinMode(4, OUTPUT);
//   pinMode(5, OUTPUT);
// }

// void loop() {
//   int d_time = 1000;
//   int LEDindex[] = {2,3,4,5}; //LEDindex[0] = 2, LEDindex[1] = 3, LEDindex[2] = 4, LEDindex[3] = 5
//   int i = 0;
//   for (i=0; i<4; i++) {
//     Serial.println(i);
//     digitalWrite(LEDindex[i], HIGH);
//     delay(d_time);
//     digitalWrite(LEDindex[i], LOW);
//     delay(d_time);
//   }
//   for (i = 2; i > 0; i--) {
//     Serial.println(i);
//     digitalWrite(LEDindex[i], HIGH);
//     delay(d_time);
//     digitalWrite(LEDindex[i], LOW);
//     delay(d_time);
//   }
// }

//EP3.7 ***********************************************************************
// void setup() {
//   Serial.begin(9600);
//   pinMode(2, OUTPUT);
//   pinMode(3, OUTPUT);
//   pinMode(4, OUTPUT);
//   pinMode(5, OUTPUT);
// }

// void loop() {
//   p_led(1,0,0,0);
//   p_led(0,1,0,1);
//   p_led(1,0,1,0);
//   p_led(0,0,0,1);
//   p_led(1,0,1,0);
//   p_led(0,1,0,1);
// }

// void p_led(int a, int b, int c, int d) {
//   int d_time = 500;
//   digitalWrite(2, a);
//   digitalWrite(3, b);
//   digitalWrite(4, c);
//   digitalWrite(5, d);
//   delay(d_time);
// }
