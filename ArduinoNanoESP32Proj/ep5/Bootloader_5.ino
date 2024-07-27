//EP5.2 การหยุดการทำงานชั่วคราวของ Ardoino nano ESP32 เพื่อเข้าสู่โหมด Bootloader
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  int d_time = 1000;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(d_time);
  digitalWrite(LED_BUILTIN, LOW);
  delay(d_time);
}