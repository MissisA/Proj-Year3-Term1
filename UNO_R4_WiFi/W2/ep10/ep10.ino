#include <TimerOne.h>
#include <Servo.h>

#define Green_LED 12
#define Red_LED 11
#define SERVO_PIN 9

Servo servo_1;
int pos = 180;

volatile bool state = false;

void setup() {
  pinMode(Green_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);

  digitalWrite(Green_LED, LOW);
  digitalWrite(Red_LED, LOW);

  Timer1.initialize(250000);
  Timer1.attachInterrupt(Doraemon);

  servo_1.attach(SERVO_PIN);
  servo_1.write(pos);

  delay(1000);

}

void Doraemon(){
  state = !state;
  digitalWrite(Green_LED, state);
}

void lood(){
  for(pos=180;pos>90;pos--){
    servo_1.write(pos);
    delay(40);
  }
  for(pos=90;pos<180;pos++){
    servo_1.write(pos);
    delay(40);
  }
}
