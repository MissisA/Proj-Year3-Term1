/*Joystick Ep1*/
// #define x_pin A0
// #define y_pin A1
// #define sw_pin 3

// void setup() {
//   pinMode(x_pin, INPUT);
//   pinMode(y_pin, INPUT);
//   pinMode(sw_pin, INPUT);

//   Serial.begin(9600);
// }

// void loop() {
//   int x_data = analogRead(x_pin);
//   int y_data = analogRead(y_pin);
//   int sw_data = digitalRead(sw_pin);

//   Serial.print("ข้อมูลจากแกน x:");
//   Serial.println(x_data);

//   Serial.print("ข้อมูลจากแกน y:");
//   Serial.println(y_data);

//   Serial.print("ข้อมูลจากปุ่มสวิตซ์:");
//   Serial.println(sw_data);

//   delay(100);
// }


/*Joystick Ep2*/
// #define x_pin A0
// #define y_pin A1
// #define sw_pin 3

// #define x_led 10
// #define y_led 9
// #define sw_led 8

// void setup() {
//   pinMode(x_pin, INPUT);
//   pinMode(y_pin, INPUT);
//   pinMode(sw_pin, INPUT);

//   pinMode(x_led, OUTPUT);
//   pinMode(y_led, OUTPUT);
//   pinMode(sw_led, OUTPUT);

//   Serial.begin(9600);
// }

// void loop() {
//   int x_data = analogRead(x_pin);
//   int y_data = analogRead(y_pin);
//   int sw_data = digitalRead(sw_pin);

//   int x_out = map(x_data,0,1023,0,255);
//   int y_out = map(y_data,0,1023,0,255);

//   analogWrite(x_led, x_out);
//   analogWrite(y_led, y_out);
//   digitalWrite(sw_led, sw_data);

//   Serial.print("ข้อมูลออที่ LED สีเขียว:");
//   Serial.println(x_out);

//   Serial.print("ข้อมูลออที่ LED สีเหลือง:");
//   Serial.println(y_out);

//   Serial.print("ข้อมูลจากปุ่มสวิตซ์:");
//   Serial.println(sw_data);

//   delay(100);
// }

/*Joystick Ep3*/
// #include <Servo.h>

// #define x_pin A0
// #define y_pin A1
// #define sw_pin 3

// #define ServoX_Pin 10
// #define ServoY_Pin 9

// Servo servo_x;
// Servo servo_y;

// int pos_x = 180;
// int pos_y = 180;

// void setup() {
//   pinMode(x_pin, INPUT);
//   pinMode(y_pin, INPUT);
//   pinMode(sw_pin, INPUT);

//   pinMode(ServoX_Pin, OUTPUT);
//   pinMode(ServoY_Pin, OUTPUT);

//   servo_x.attach(ServoX_Pin);
//   servo_x.write(pos_x);
//   servo_y.attach(ServoY_Pin);
//   servo_y.write(pos_y);

//   delay(1000);
// }

// void loop() {
//   int x_data = analogRead(x_pin);
//   int y_data = analogRead(y_pin);
//   int sw_data = digitalRead(sw_pin);

  
//   pos_x = map(x_data,0,1023,0,180);
//   pos_y = map(y_data,0,1023,0,180);

//   servo_x.write(pos_x);
//   servo_y.write(pos_y);

//   delay(40);
// }