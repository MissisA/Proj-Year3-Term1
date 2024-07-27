//ep5.3
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard; //object ตัวแปร

void setup() {
  Keyboard.begin(); //เริ่มทำงาน
  USB.begin();
}

void loop() {
  Keyboard.press('A');//เหมือนเอานิ้วไปกดที่ตัวอักษร
  delay(100); //กดค้างไว้
  Keyboard.releaseAll();//เหมือนปล่อย
  delay(1000);
}

//ep5.4 https://github.com/espressif/arduino-esp32/blob/master/libraries/USB/src/USBHIDKeyboard.h
// #include "USB.h"
// #include "USBHIDKeyboard.h"
// USBHIDKeyboard Keyboard;

// void setup() {
//   Keyboard.begin();
//   USB.begin();
// }

// void loop() {
//   Keyboard.press(KEY_ESC);
//   delay(100);
//   Keyboard.releaseAll();
//   delay(10000);
// }

//EP5.5  การทำ HID Keyboard (3/6) สำหรับ Arduino Nano ESP32
// #include "USB.h"
// #include "USBHIDKeyboard.h"
// USBHIDKeyboard Keyboard;

// void setup() {
//   Keyboard.begin();
//   USB.begin();
//   pinMode(17, INPUT);
// }

// void loop() {
//   int kb_1 = digitalRead(17);
//   if(kb_1 == 1){
//   Keyboard.press('A');
//   delay(100);
//   Keyboard.releaseAll();
//   delay(500);
//   }
// }

//EP5.6 การทำ HID Keyboard (4/6) สำหรับ Arduino Nano ESP32
// #include "USB.h"
// #include "USBHIDKeyboard.h"
// USBHIDKeyboard Keyboard;

// void setup() {
//   Keyboard.begin();
//   USB.begin();
//   pinMode(17, INPUT);
// }

// void loop() {
//   int kb_1 = digitalRead(17);
//   if(kb_1 == 1){
//   Keyboard.press(KEY_LEFT_GUI); //MacOS
//   // Keyboard.press(KEY_LEFT_CTRL); //Windows
//   Keyboard.press(KEY_LEFT_ALT);
//   Keyboard.press(KEY_DELETE);
//   delay(100);
//   Keyboard.releaseAll();
//   delay(500);
//   }
// }

//EP5.7 การทำ HID Keyboard (5/6) สำหรับ Arduino Nano ESP32
// #include "USB.h"
// #include "USBHIDKeyboard.h"
// USBHIDKeyboard Keyboard;

// void setup() {
//   Keyboard.begin();
//   USB.begin();
//   pinMode(17, INPUT);
// }

// void loop() {
//   int kb_1 = digitalRead(17);
//   if(kb_1 == 1){
//   Keyboard.println("University of phayao");
//   // Keyboard.println(); #Enter
//   delay(500);
//   }
// }

//EP5.8 การทำ HID Keyboard (6/6) สำหรับ Arduino Nano ESP32
// #include "USB.h"
// #include "USBHIDKeyboard.h"
// USBHIDKeyboard Keyboard;

// void setup() {
//   Keyboard.begin();
//   USB.begin();
//   pinMode(17, INPUT);
//   pinMode(18, INPUT);
//   pinMode(19, INPUT);
//   pinMode(20, INPUT);
// }

// void loop() {
//   int kb_1 = digitalRead(17);
//   int kb_2 = digitalRead(18);
//   int kb_3 = digitalRead(19);
//   int kb_4 = digitalRead(20);

//   if(kb_1 == 1){
//   Keyboard.press(KEY_LEFT_ARROW);
//   delay(100);
//   Keyboard.releaseAll();
//   delay(100);
//   }else if(kb_2 == 1){
//   Keyboard.press(KEY_UP_ARROW);
//   delay(100);
//   Keyboard.releaseAll();
//   delay(100);
//   }else if(kb_3 == 1){
//   Keyboard.press(KEY_DOWN_ARROW);
//   delay(100);
//   Keyboard.releaseAll();
//   delay(100);
//   }else if(kb_4 == 1){
//   Keyboard.press(KEY_RIGHT_ARROW);
//   delay(100);
//   Keyboard.releaseAll();
//   delay(100);
//   }
// }

//EP5.9 การทำ HID (Human Interface Device) สำหรับ Mouse ของ Arduino Nano ESP32
// #include "USB.h"
// #include "USBHIDMouse.h"
// USBHIDMouse Mouse;

// void setup() {
//   Mouse.begin();
//   USB.begin();
// }

// void loop() {
//   Mouse.move(100, 100, 0);
//   delay(500);
//   Mouse.move(-100, -100, 0);
//   delay(500);

// }

//EP5.10 การเลื่อน Scroll Mouse กรณี HID สำหรับ Arduino Nano ESP32
// #include "USB.h"
// #include "USBHIDMouse.h"
// USBHIDMouse Mouse;

// void setup() {
//   Mouse.begin();
//   USB.begin();
// }

// void loop() {
//   // Mouse.move(0, 0, 3000); //เคอร์เซอร์ตรงกลาง เลื่อนขึ้น ลง 
//   // delay(250);

//   // Mouse.move(0, 0, 0, 3000); //เคอร์เซอร์แกนX เลื่อนทางซ้าย ขวา 
//   // delay(250);
// }

//EP5.11 การควบคุมปุ่มคลิกซ้ายและขวาของ Mouse กรณี HID สำหรับ Arduino Nano ESP32
// #include "USB.h"
// #include "USBHIDMouse.h"
// USBHIDMouse Mouse;

// void setup() {
//   Mouse.begin();
//   USB.begin();
// }

// void loop() {
//   // Mouse.press(); //คลิกซ้าย1
//   // Mouse.press(MOUSE_LEFT); //คลิกซ้าย2
//   Mouse.press(MOUSE_RIGHT); //คลิกขวา
//   delay(100);
//   // Mouse.ereleas(); //1
//   // Mouse.ereleas(MOUSE_LEFT); //2                  
//   Mouse.release(MOUSE_RIGHT);
//   delay(1000);
// }

//EP5.12 การใช้ปุ่มสวิตช์เพื่อควบคุม Mouse กรณี HID สำหรับ Arduino Nano ESP32
#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup(){}
void loop(){}
#else

#include "USB.h"
#include "USBHIDMouse.h"
USBHIDMouse Mouse;


// set pin numbers for the five buttons:
const int upButton = 17;
const int downButton = 18;
const int leftButton = 19;
const int rightButton = 20;
const int mouseButton = 2;

int range = 5;              // output range of X or Y movement; affects movement speed
int responseDelay = 10;     // response delay of the mouse, in ms


void setup() {
  // initialize the buttons' inputs:
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(mouseButton, INPUT);
  // initialize mouse control:
  Mouse.begin();
  USB.begin();
}

void loop() {
  // read the buttons:
  int upState = digitalRead(upButton);
  int downState = digitalRead(downButton);
  int rightState = digitalRead(rightButton);
  int leftState = digitalRead(leftButton);
  int clickState = digitalRead(mouseButton);

  // calculate the movement distance based on the button states:
  int  xDistance = (leftState - rightState) * range;
  int  yDistance = (upState - downState) * range;

  // if X or Y is non-zero, move:
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }

  // if the mouse button is pressed:
  if (clickState == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}
#endif /* ARDUINO_USB_MODE */