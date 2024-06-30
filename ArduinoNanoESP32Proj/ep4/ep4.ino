//ep4.2
void setup() {
  Serial.begin(9600);
  pinMode(17, INPUT);

}

void loop() {
  int a;
  a = digitalRead(17);

  Serial.println(a);
  delay(10);

}

//ep4.3
void setup() {
  Serial.begin(9600);
  pinMode(17, INPUT);

}

void loop() {
  int a;
  a = digitalRead(17);
  if (a == 1){
    Serial.println("มีการกดปุ่ม");
  }
  else {
    Serial.println("ไม่ได้กดปุ่ม");
  }
  delay(10);
}
//4.4
void setup() {
  pinMode(17, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  int a;
  a = digitalRead(17);
  if (a == 1){
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  delay(10);
}
//4.5 pull down
void setup() {
  pinMode(17, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); //ขา13
  pinMode(LED_RED, OUTPUT); //14
  pinMode(LED_GREEN, OUTPUT); //15
  pinMode(LED_BLUE, OUTPUT); //16

}

void loop() {
  int a;
  a = digitalRead(17);
  if (a == 1){
    digitalWrite(LED_BUILTIN, HIGH);
    led_pat();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
  }
  delay(10);
}

void led_pat(){
  digitalWrite(LED_RED, LOW);
  delay(100);
  digitalWrite(LED_RED, HIGH);

  digitalWrite(LED_GREEN, LOW);
  delay(100);
  digitalWrite(LED_GREEN, HIGH);

  digitalWrite(LED_BLUE, LOW);
  delay(100);
  digitalWrite(LED_BLUE, HIGH);
}
//4.6 pull up
void setup() {
  pinMode(17, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); //ขา13
  pinMode(LED_RED, OUTPUT); //14
  pinMode(LED_GREEN, OUTPUT); //15
  pinMode(LED_BLUE, OUTPUT); //16

}

void loop() {
  int a;
  a = digitalRead(17);
  if (a == 0){
    digitalWrite(LED_BUILTIN, HIGH);
    led_pat();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
  }
  delay(10);
}

void led_pat(){
  digitalWrite(LED_RED, LOW);
  delay(100);
  digitalWrite(LED_RED, HIGH);

  digitalWrite(LED_GREEN, LOW);
  delay(100);
  digitalWrite(LED_GREEN, HIGH);

  digitalWrite(LED_BLUE, LOW);
  delay(100);
  digitalWrite(LED_BLUE, HIGH);
}