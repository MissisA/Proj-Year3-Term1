#define ledPin_4 4
#define ledPin_5 5
#define ledPin_7 7
#define ledPin_9 9
#define ledPin_10 10
#define ledPin_13 13


#define buttonPin_IRQ0 3
#define buttonPin_IRQ1 2
#define buttonPin_IRQ2 17
#define buttonPin_IRQ4 6
#define buttonPin_IRQ5 1
#define buttonPin_IRQ6 0
#define buttonPin_IRQ7 16
#define buttonPin_IRQ9 8

volatile bool state_4 = false;
volatile bool state_5 = false;
volatile bool state_7 = false;
volatile bool state_9 = false;
volatile bool state_10 = false;
volatile bool state_13 = false;

volatile int prev_time = 0;

void setup() {
  pinMode(ledPin_4, OUTPUT);
  pinMode(ledPin_5, OUTPUT);
  pinMode(ledPin_7, OUTPUT);
  pinMode(ledPin_9, OUTPUT);
  pinMode(ledPin_10, OUTPUT);
  pinMode(ledPin_13, OUTPUT);

  pinMode(buttonPin_IRQ0, INPUT);
  pinMode(buttonPin_IRQ1, INPUT);
  pinMode(buttonPin_IRQ2, INPUT);
  pinMode(buttonPin_IRQ4, INPUT);
  pinMode(buttonPin_IRQ5, INPUT);
  pinMode(buttonPin_IRQ6, INPUT);
  pinMode(buttonPin_IRQ7, INPUT);
  pinMode(buttonPin_IRQ9, INPUT);

  digitalWrite(ledPin_4, LOW);
  digitalWrite(ledPin_5, LOW);
  digitalWrite(ledPin_7, LOW);
  digitalWrite(ledPin_9, LOW);
  digitalWrite(ledPin_10, LOW);
  digitalWrite(ledPin_13, LOW);

  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ0), ISR_IRQ0, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ1), ISR_IRQ1, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ2), ISR_IRQ2, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ4), ISR_IRQ4, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ5), ISR_IRQ5, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ6), ISR_IRQ6, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ7), ISR_IRQ7, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin_IRQ9), ISR_IRQ9, LOW);

}

void ISR_IRQ0(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    state_4 = !state_4;
    digitalWrite(ledPin_4, state_4);
  }
}

void ISR_IRQ1(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    state_5 = !state_5;
    digitalWrite(ledPin_5, state_5);
  }
}

void ISR_IRQ2(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    state_7 = !state_7;
    digitalWrite(ledPin_7, state_7);
  }
}

void ISR_IRQ4(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    state_9 = !state_9;
    digitalWrite(ledPin_9, state_9);
  }
}

void ISR_IRQ5(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    state_10 = !state_10;
    digitalWrite(ledPin_10, state_10);
  }
}

void ISR_IRQ6(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    state_13 = !state_13;
    digitalWrite(ledPin_13, state_13);
  }
}

void ISR_IRQ7(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    digitalWrite(ledPin_4, HIGH);
    digitalWrite(ledPin_5, HIGH);
    digitalWrite(ledPin_7, HIGH);
    digitalWrite(ledPin_9, HIGH);
    digitalWrite(ledPin_10, HIGH);
    digitalWrite(ledPin_13, HIGH);
  }
}

void ISR_IRQ9(){
  if(millis() - prev_time >= 250){
    prev_time = millis();
    digitalWrite(ledPin_4, LOW);
    digitalWrite(ledPin_5, LOW);
    digitalWrite(ledPin_7, LOW);
    digitalWrite(ledPin_9, LOW);
    digitalWrite(ledPin_10, LOW);
    digitalWrite(ledPin_13, LOW);
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
