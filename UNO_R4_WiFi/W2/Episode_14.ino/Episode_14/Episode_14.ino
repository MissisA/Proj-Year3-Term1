// //Episode 14 ตอนที่ 4 การส่งข้อมูลจาก Arduino Nano ESP32 ไปเก็บไว้บน Firebase (Read)
// #include <WiFi.h> //ไลบารี่ไวไฟ
// #include <Firebase_ESP_Client.h> //ไลบารี่ไฟล์เบส
// #include "addons/TokenHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อสร้างโทเคน
// #include "addons/RTDBHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อเพย์โหลดเก็บข้อมูล (Printing) ลงในดาต้าเบสแบบเรียล์ไทม์ (Realtime Database: RTDB) และการช่วยเหลืออื่น ๆ

// #define WIFI_SSID "PY" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "12345678" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

// #define API_KEY "AIzaSyANfLhwcWr4tJ6yup682_RuSdaW8ehU3-g" //ค่า Web API Key ที่ได้จากการสร้างบนไฟล์เบส
// #define DATABASE_URL "https://dontreefirebase-default-rtdb.asia-southeast1.firebasedatabase.app/" //ลิงค์ URL ของดาต้าเบส ได้จากการสร้างบนไฟล์เบส

// // #define LED1_PIN 2 //กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 2
// // #define LED2_PIN 3 //กำหนดใช้งานขาเอaาต์พุตแอลอีดีที่ขา 3
// #define ANA_PIN A0 //กำหนดขาอินพุตที่เป็นแอนาล็อกไว้ที่ขา A0

// FirebaseData fbdo; //สร้างอ็อปเจ็คที่ชื่อว่า fbdo (FireBase Data Output)สำหรับค่าเอาต์พุตดาต้าที่ไมโครเมื่อมีการเปลี่ยนแปลงค่าที่เซ็นเซอร์
// FirebaseAuth auth; //สร้างอ็อปเจ็คที่ชื่อว่า auth (Firebase Authentication) เพื่อใช้สำหรับการยืนยันตัวตนในกรณีที่เข้าใช้งาน Firebase
// FirebaseConfig config; //สร้างอ็อปเจ็คที่ชื่อว่า config เพื่อใช้สำหรับการตั้งค่าต่าง ๆ ระหว่างไมโครคอนโทรเลอร์และไฟล์เบส

// unsigned long sendDataPreMillis = 0; //สร้างตัวแปรชนิด unsigned long เพื่อใช้กับฟังก์ชั่น millis() สำหรับการส่งข้อมูลไปกลับระหว่างไมโครคอนโทรเลอร์และไฟล์เบส
// boolean signupOK = false; //ตัวแปรแบบ bool ใช้เพื่อเก็บค่าการ sing up ของไฟล์เบสว่าสำเร็จหรือไม่ ถ้าสำเร็จให้เก็บค่า 1 ถ้าไม่สำเร็จให้เก็บค่า 0
// int analogData = 0; //ตัวแปรแบบ int ใช้เก็บข้อมูลขาแอนาล็อกที่ขา A0 โดยมีค่าระหว่าง 0 ถึง 4095
// float voltage = 0.0; //ตัวแปรแบบ float ใช้เพื่อแปลงค่า analogData ให้เป็นค่าแรงดันไฟฟ้าที่ป้อนเข้ามาที่ขา A0

// void setup() {
//   Serial.begin(9600); //กำหนดอัตราบอร์ดเรตสำหรับติดต่อกับ Serial Monitor อยู่ที่ 115200 บิตต่อวินาที
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //สั่งให้ไวไฟทำงาน โดยอ้างอิงชื่อเราเตอร์และพาสเวิร์ดจาก WIFI_SSID และ WIFI_PASSWORD ที่สร้างจากข้างบน
//   Serial.print("กำลังเชื่อมต่อไวไฟ..."); //แสดงข้อความขณะกำลังเชื่อมต่อไวไฟ
//   while(WiFi.status() != WL_CONNECTED){ // ทำการตรวจสอบการเชื่อมต่อไวไฟว่าเชื่อมต่อแล้วหรือยัง ถ้ายังให้ทำงานในเงื่อนไขข้างล่างในวงเล็บ แต่ถ้าเชื่อมต่อสำเร็จก็ให้หลุดลูปไป
//     Serial.print("."); //พิมพ์จุดไป 1 จุด
//     delay(300); //ดีเลย์ไป 300 มิลลิวินาที
//   }
//   Serial.println(); //ขึ้นบรรทัดใหม่
//   Serial.print("เชื่อมต่อไวไฟสำเร็จ และมีเบอร์ IP คือ "); //แสดงข้อความเมื่อเชื่อมต่อไวไฟสำเร็จ
//   Serial.println(WiFi.localIP()); //แสดงเบอร์ไอพีแอดเดรสของไมโครที่เชื่อมต่อกับเราเตอร์
//   Serial.println(); //ขึ้นบรรทัดใหม่

//   config.api_key = API_KEY; //กำหนดค่า API KEY เพื่อใช้เชื่อมต่อกับไฟล์เบส
//   config.database_url = DATABASE_URL; //กำหนดค่า DATABASE URL เพื่อใช้เชื่อมต่อกับไฟล์เบส

//   if(Firebase.signUp(&config, &auth, "", "")){ //คำสั่ง sign up บนไฟล์เบส โดยให้เอาค่าที่ได้จาก config ข้างบนและ Authentication มาทำการ sign up ในฐานะ anonymous (บุคคลที่ไร้ตัวตน) ใส่เครื่องหมาย "" ทั้งสองตัว โดยทุกครั้งที่ไมโครคอนโทรเลอร์ทำการเชื่อมต่อไปที่ไฟล์เบส จะทำการสร้างยูสเซอร์ใหม่ที่เป็น anonymous ทุกครั้งไป
//     Serial.println("ทำการเชื่อมต่อไฟล์เบสสำเร็จในฐานะ Anonymous"); //แสดงข้อความในกรณีที่ sign up สำเร็จ
//     signupOK = true;
//   }
//   else{
//     Serial.printf("%s\n", config.signer.signupError.message.c_str()); //ถ้าการเชื่อมต่อไม่สำเร็จให้แสดงข้อความตามที่ helper ของ firebase ได้ทำการตั้งค่าเอาไว้ (เราไม่ต้องพิมพ์เอง ให้ระบบเจ็นข้อมูลมาแสดง)
//   }

//   config.token_status_callback = tokenStatusCallback; //ทำการตรวจสอบสอบ Token ระหว่างไมโครคอนโทรเลอร์และตัวไฟล์เบส
//   Firebase.begin(&config, &auth); //เริ่มต้นการทำงานไฟล์เบส โดยใช้้ข้อมูล config และ Authentication ที่ได้ทำการสร้างจากข้างบน
//   Firebase.reconnectWiFi(true); //ตรวจสอบสถานะการทำงานของไวไฟที่ใช้เชื่อมต่อไฟล์เบส
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(Firebase.ready() && signupOK && (millis() - sendDataPreMillis > 5000 || sendDataPreMillis == 0)){ //ตรวจสอบว่าไฟล์เบสพร้อมทำงานหรือยัง และ การ signup เรียบร้อยแล้ว โดยจะทำการทำงานลูปในวงเล็บข้างล่างทุก ๆ 5 วินาทีผ่านฟังก์ชั่น millis()
//     sendDataPreMillis = millis();
    
//     analogData = analogRead(ANA_PIN); //การอ่านค่าแอนาล็อกจากขา A0 มาเก็บไว้ที่ตัวแปร analogData
//     voltage = (float)analogReadMilliVolts(ANA_PIN)/1000; //ทำการแปลงค่าจากอินพุตแอนาล็อกที่ขา A0 ให้เป็นค่าแรงดันไฟฟ้าโดยใช้ฟังก์ชั่น analogReadMilliVolts() หน่วยที่ได้เป็นมิลลิโวลต์จึงต้องเอา 1000 ไปหาร แล้วเอามาเก็บไว้ที่ตัวแปร voltage 

//     // การส่งข้อมูลแบบ Integer ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setInt(&fbdo, "Sensor/ana_data", analogData)){ //ทำการตรวจสอบค่า analogData ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/ana_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(analogData); //พิมพ์ค่าตัวแปร analogData
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การส่งข้อมูลแบบ Floating ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setFloat(&fbdo, "Sensor/voltage", voltage)){ //ทำการตรวจสอบค่า voltage ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/voltage
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(voltage); //พิมพ์ค่าตัวแปร voltage
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }
//   }

// }



//Episode 14 ตอนที่ 5 การรับข้อมูลจาก Firebase มาควบคุมอุปกรณ์ที่ Arduino Nano ESP32 (Write)
// #include <WiFi.h> //ไลบารี่ไวไฟ
// #include <Firebase_ESP_Client.h> //ไลบารี่ไฟล์เบส
// #include "addons/TokenHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อสร้างโทเคน
// #include "addons/RTDBHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อเพย์โหลดเก็บข้อมูล (Printing) ลงในดาต้าเบสแบบเรียล์ไทม์ (Realtime Database: RTDB) และการช่วยเหลืออื่น ๆ

// #define WIFI_SSID "PY" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "12345678" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

// #define API_KEY "AIzaSyANfLhwcWr4tJ6yup682_RuSdaW8ehU3-g" //ค่า Web API Key ที่ได้จากการสร้างบนไฟล์เบส
// #define DATABASE_URL "https://dontreefirebase-default-rtdb.asia-southeast1.firebasedatabase.app/" //ลิงค์ URL ของดาต้าเบส ได้จากการสร้างบนไฟล์เบส

// // #define LED1_PIN 2 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 2
// // #define LED2_PIN 3 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 3
// #define ANA_PIN A0 //กำหนดขาอินพุตที่เป็นแอนาล็อกไว้ที่ขา A0

// #define PWM_PIN 4 //** กำหนดการใช้งานขา Pulse Width Modulation เอาไว้ที่ขา 4 เป็นอินพุต
// #define LEDdigital 5 //** กำหนดการใช้งานขาเอาต์พุตดิจิตอลที่ต่อออกขา 5

// FirebaseData fbdo; //สร้างอ็อปเจ็คที่ชื่อว่า fbdo (FireBase Data Output)สำหรับค่าเอาต์พุตดาต้าที่ไมโครเมื่อมีการเปลี่ยนแปลงค่าที่เซ็นเซอร์
// FirebaseAuth auth; //สร้างอ็อปเจ็คที่ชื่อว่า auth (Firebase Authentication) เพื่อใช้สำหรับการยืนยันตัวตนในกรณีที่เข้าใช้งาน Firebase
// FirebaseConfig config; //สร้างอ็อปเจ็คที่ชื่อว่า config เพื่อใช้สำหรับการตั้งค่าต่าง ๆ ระหว่างไมโครคอนโทรเลอร์และไฟล์เบส

// unsigned long sendDataPreMillis = 0; //สร้างตัวแปรชนิด unsigned long เพื่อใช้กับฟังก์ชั่น millis() สำหรับการส่งข้อมูลไปกลับระหว่างไมโครคอนโทรเลอร์และไฟล์เบส
// boolean signupOK = false; //ตัวแปรแบบ bool ใช้เพื่อเก็บค่าการ sing up ของไฟล์เบสว่าสำเร็จหรือไม่ ถ้าสำเร็จให้เก็บค่า 1 ถ้าไม่สำเร็จให้เก็บค่า 0
// int analogData = 0; //ตัวแปรแบบ int ใช้เก็บข้อมูลขาแอนาล็อกที่ขา A0 โดยมีค่าระหว่าง 0 ถึง 4095
// float voltage = 0.0; //ตัวแปรแบบ float ใช้เพื่อแปลงค่า analogData ให้เป็นค่าแรงดันไฟฟ้าที่ป้อนเข้ามาที่ขา A0

// int pwmValue = 0; //** ตัวแปรแบบ PWM ที่ใช้ขับออกที่ขา 4 0-255
// bool ledStatus  = false; //** ตัวแปรขับ LED ที่ขาดิจิตอลที่ขา 5 โดยกำหนดให้เป็นดับก่อน (0)


// void setup() {
//   Serial.begin(9600); //กำหนดอัตราบอร์ดเรตสำหรับติดต่อกับ Serial Monitor อยู่ที่ 115200 บิตต่อวินาที
//   pinMode(PWM_PIN, OUTPUT); //** กำหนดให้ขาเอาต์พุต PWM ไว้ที่ขา 4
//   pinMode(LEDdigital, OUTPUT); //** กำหนดให้ขาเอาต์พุตดิจิตอลไว้ที่ขา 5
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //สั่งให้ไวไฟทำงาน โดยอ้างอิงชื่อเราเตอร์และพาสเวิร์ดจาก WIFI_SSID และ WIFI_PASSWORD ที่สร้างจากข้างบน
//   Serial.print("กำลังเชื่อมต่อไวไฟ..."); //แสดงข้อความขณะกำลังเชื่อมต่อไวไฟ
//   while(WiFi.status() != WL_CONNECTED){ // ทำการตรวจสอบการเชื่อมต่อไวไฟว่าเชื่อมต่อแล้วหรือยัง ถ้ายังให้ทำงานในเงื่อนไขข้างล่างในวงเล็บ แต่ถ้าเชื่อมต่อสำเร็จก็ให้หลุดลูปไป
//     Serial.print("."); //พิมพ์จุดไป 1 จุด
//     delay(300); //ดีเลย์ไป 300 มิลลิวินาที
//   }
//   Serial.println(); //ขึ้นบรรทัดใหม่
//   Serial.print("เชื่อมต่อไวไฟสำเร็จ และมีเบอร์ IP คือ "); //แสดงข้อความเมื่อเชื่อมต่อไวไฟสำเร็จ
//   Serial.println(WiFi.localIP()); //แสดงเบอร์ไอพีแอดเดรสของไมโครที่เชื่อมต่อกับเราเตอร์
//   Serial.println(); //ขึ้นบรรทัดใหม่

//   config.api_key = API_KEY; //กำหนดค่า API KEY เพื่อใช้เชื่อมต่อกับไฟล์เบส
//   config.database_url = DATABASE_URL; //กำหนดค่า DATABASE URL เพื่อใช้เชื่อมต่อกับไฟล์เบส

//   if(Firebase.signUp(&config, &auth, "", "")){ //คำสั่ง sign up บนไฟล์เบส โดยให้เอาค่าที่ได้จาก config ข้างบนและ Authentication มาทำการ sign up ในฐานะ anonymous (บุคคลที่ไร้ตัวตน) ใส่เครื่องหมาย "" ทั้งสองตัว โดยทุกครั้งที่ไมโครคอนโทรเลอร์ทำการเชื่อมต่อไปที่ไฟล์เบส จะทำการสร้างยูสเซอร์ใหม่ที่เป็น anonymous ทุกครั้งไป
//     Serial.println("ทำการเชื่อมต่อไฟล์เบสสำเร็จในฐานะ Anonymous"); //แสดงข้อความในกรณีที่ sign up สำเร็จ
//     signupOK = true;
//   }
//   else{
//     Serial.printf("%s\n", config.signer.signupError.message.c_str()); //ถ้าการเชื่อมต่อไม่สำเร็จให้แสดงข้อความตามที่ helper ของ firebase ได้ทำการตั้งค่าเอาไว้ (เราไม่ต้องพิมพ์เอง ให้ระบบเจ็นข้อมูลมาแสดง)
//   }

//   config.token_status_callback = tokenStatusCallback; //ทำการตรวจสอบสอบ Token ระหว่างไมโครคอนโทรเลอร์และตัวไฟล์เบส
//   Firebase.begin(&config, &auth); //เริ่มต้นการทำงานไฟล์เบส โดยใช้้ข้อมูล config และ Authentication ที่ได้ทำการสร้างจากข้างบน
//   Firebase.reconnectWiFi(true); //ตรวจสอบสถานะการทำงานของไวไฟที่ใช้เชื่อมต่อไฟล์เบส
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(Firebase.ready() && signupOK && (millis() - sendDataPreMillis > 5000 || sendDataPreMillis == 0)){ //ตรวจสอบว่าไฟล์เบสพร้อมทำงานหรือยัง และ การ signup เรียบร้อยแล้ว โดยจะทำการทำงานลูปในวงเล็บข้างล่างทุก ๆ 5 วินาทีผ่านฟังก์ชั่น millis()
//     sendDataPreMillis = millis();
    
//     analogData = analogRead(ANA_PIN); //การอ่านค่าแอนาล็อกจากขา A0 มาเก็บไว้ที่ตัวแปร analogData
//     voltage = (float)analogReadMilliVolts(ANA_PIN)/1000; //ทำการแปลงค่าจากอินพุตแอนาล็อกที่ขา A0 ให้เป็นค่าแรงดันไฟฟ้าโดยใช้ฟังก์ชั่น analogReadMilliVolts() หน่วยที่ได้เป็นมิลลิโวลต์จึงต้องเอา 1000 ไปหาร แล้วเอามาเก็บไว้ที่ตัวแปร voltage 

//     // การส่งข้อมูลแบบ Integer ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setInt(&fbdo, "Sensor/ana_data", analogData)){ //ทำการตรวจสอบค่า analogData ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/ana_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(analogData); //พิมพ์ค่าตัวแปร analogData
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การส่งข้อมูลแบบ Floating ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setFloat(&fbdo, "Sensor/voltage", voltage)){ //ทำการตรวจสอบค่า voltage ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/voltage
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(voltage); //พิมพ์ค่าตัวแปร voltage
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//      // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ PWM (แอนาล็อกเสมือน)
//     if(Firebase.RTDB.getInt(&fbdo, "/LED/analog")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/analog
//       if(fbdo.dataType()=="int"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ int หรือไม่
//         pwmValue = fbdo.intData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร pwmValue
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + pwmValue + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         analogWrite(PWM_PIN, pwmValue); //นำค่าที่ได้ไปขับแอนาล็อกเอาต์พุต (PWM) ที่ขา 4
//         delay(100); //ดีเลย์การขับ PWM ที่ขา 4 อยู่ที่ 100 ไมโครวินาที
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปร boolean เพื่อขับการติดและดับของ LED ที่ขา 5
//     if(Firebase.RTDB.getBool(&fbdo, "/LED/digital")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/digital
//       if(fbdo.dataType()=="boolean"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ boolean หรือไม่
//         ledStatus = fbdo.boolData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร ledStatus
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + ledStatus + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         digitalWrite(LEDdigital, ledStatus); //นำค่าที่ได้ไปขับดิจิตอลเอาต์พุตที่ขา 5
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }
//   }
// }



//Episode 14 ตอนที่ 6 การใช้งาน PIR Sensor เพื่อตรวจจับสำหรับการรายงานข้อมูลไปยัง Firebase
// #include <WiFi.h> //ไลบารี่ไวไฟ
// #include <Firebase_ESP_Client.h> //ไลบารี่ไฟล์เบส
// #include "addons/TokenHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อสร้างโทเคน
// #include "addons/RTDBHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อเพย์โหลดเก็บข้อมูล (Printing) ลงในดาต้าเบสแบบเรียล์ไทม์ (Realtime Database: RTDB) และการช่วยเหลืออื่น ๆ

// #define WIFI_SSID "PY" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "12345678" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

// #define API_KEY "AIzaSyANfLhwcWr4tJ6yup682_RuSdaW8ehU3-g" //ค่า Web API Key ที่ได้จากการสร้างบนไฟล์เบส
// #define DATABASE_URL "https://dontreefirebase-default-rtdb.asia-southeast1.firebasedatabase.app/" //ลิงค์ URL ของดาต้าเบส ได้จากการสร้างบนไฟล์เบส

// // #define LED1_PIN 2 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 2
// // #define LED2_PIN 3 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 3
// #define ANA_PIN A0 //กำหนดขาอินพุตที่เป็นแอนาล็อกไว้ที่ขา A0

// #define PWM_PIN 4 //** กำหนดการใช้งานขา Pulse Width Modulation เอาไว้ที่ขา 4 เป็นอินพุต
// #define LEDdigital 5 //** กำหนดการใช้งานขาเอาต์พุตดิจิตอลที่ต่อออกขา 5
// #define PIR_PIN 6 //*** กำหนดการใช้งานขาอินพุตดิจิตอลที่ต่อเข้าขา 6 ของ PIR Sensor

// FirebaseData fbdo; //สร้างอ็อปเจ็คที่ชื่อว่า fbdo (FireBase Data Output)สำหรับค่าเอาต์พุตดาต้าที่ไมโครเมื่อมีการเปลี่ยนแปลงค่าที่เซ็นเซอร์
// FirebaseAuth auth; //สร้างอ็อปเจ็คที่ชื่อว่า auth (Firebase Authentication) เพื่อใช้สำหรับการยืนยันตัวตนในกรณีที่เข้าใช้งาน Firebase
// FirebaseConfig config; //สร้างอ็อปเจ็คที่ชื่อว่า config เพื่อใช้สำหรับการตั้งค่าต่าง ๆ ระหว่างไมโครคอนโทรเลอร์และไฟล์เบส

// unsigned long sendDataPreMillis = 0; //สร้างตัวแปรชนิด unsigned long เพื่อใช้กับฟังก์ชั่น millis() สำหรับการส่งข้อมูลไปกลับระหว่างไมโครคอนโทรเลอร์และไฟล์เบส
// boolean signupOK = false; //ตัวแปรแบบ bool ใช้เพื่อเก็บค่าการ sing up ของไฟล์เบสว่าสำเร็จหรือไม่ ถ้าสำเร็จให้เก็บค่า 1 ถ้าไม่สำเร็จให้เก็บค่า 0
// int analogData = 0; //ตัวแปรแบบ int ใช้เก็บข้อมูลขาแอนาล็อกที่ขา A0 โดยมีค่าระหว่าง 0 ถึง 4095
// float voltage = 0.0; //ตัวแปรแบบ float ใช้เพื่อแปลงค่า analogData ให้เป็นค่าแรงดันไฟฟ้าที่ป้อนเข้ามาที่ขา A0

// int pwmValue = 0; //** ตัวแปรแบบ PWM ที่ใช้ขับออกที่ขา 4 0-255
// bool ledStatus  = false; //** ตัวแปรขับ LED ที่ขาดิจิตอลที่ขา 5 โดยกำหนดให้เป็นดับก่อน (0)
// bool state = false; //*** ตัวแปรใช้รับค่า PIR Sensor ที่ขาดิจิตอลที่ขา 6 โดยกำหนดให้เป็น 0 ก่อน (0)


// void setup() {
//   Serial.begin(9600); //กำหนดอัตราบอร์ดเรตสำหรับติดต่อกับ Serial Monitor อยู่ที่ 115200 บิตต่อวินาที
//   pinMode(PWM_PIN, OUTPUT); //** กำหนดให้ขาเอาต์พุต PWM ไว้ที่ขา 4
//   pinMode(LEDdigital, OUTPUT); //** กำหนดให้ขาเอาต์พุตดิจิตอลไว้ที่ขา 5
//   pinMode(PIR_PIN, INPUT); //*** กำหนดให้ขาอินพุตดิจิตอลไว้ที่ขา 6
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //สั่งให้ไวไฟทำงาน โดยอ้างอิงชื่อเราเตอร์และพาสเวิร์ดจาก WIFI_SSID และ WIFI_PASSWORD ที่สร้างจากข้างบน
//   Serial.print("กำลังเชื่อมต่อไวไฟ..."); //แสดงข้อความขณะกำลังเชื่อมต่อไวไฟ
//   while(WiFi.status() != WL_CONNECTED){ // ทำการตรวจสอบการเชื่อมต่อไวไฟว่าเชื่อมต่อแล้วหรือยัง ถ้ายังให้ทำงานในเงื่อนไขข้างล่างในวงเล็บ แต่ถ้าเชื่อมต่อสำเร็จก็ให้หลุดลูปไป
//     Serial.print("."); //พิมพ์จุดไป 1 จุด
//     delay(300); //ดีเลย์ไป 300 มิลลิวินาที
//   }
//   Serial.println(); //ขึ้นบรรทัดใหม่
//   Serial.print("เชื่อมต่อไวไฟสำเร็จ และมีเบอร์ IP คือ "); //แสดงข้อความเมื่อเชื่อมต่อไวไฟสำเร็จ
//   Serial.println(WiFi.localIP()); //แสดงเบอร์ไอพีแอดเดรสของไมโครที่เชื่อมต่อกับเราเตอร์
//   Serial.println(); //ขึ้นบรรทัดใหม่

//   config.api_key = API_KEY; //กำหนดค่า API KEY เพื่อใช้เชื่อมต่อกับไฟล์เบส
//   config.database_url = DATABASE_URL; //กำหนดค่า DATABASE URL เพื่อใช้เชื่อมต่อกับไฟล์เบส

//   if(Firebase.signUp(&config, &auth, "", "")){ //คำสั่ง sign up บนไฟล์เบส โดยให้เอาค่าที่ได้จาก config ข้างบนและ Authentication มาทำการ sign up ในฐานะ anonymous (บุคคลที่ไร้ตัวตน) ใส่เครื่องหมาย "" ทั้งสองตัว โดยทุกครั้งที่ไมโครคอนโทรเลอร์ทำการเชื่อมต่อไปที่ไฟล์เบส จะทำการสร้างยูสเซอร์ใหม่ที่เป็น anonymous ทุกครั้งไป
//     Serial.println("ทำการเชื่อมต่อไฟล์เบสสำเร็จในฐานะ Anonymous"); //แสดงข้อความในกรณีที่ sign up สำเร็จ
//     signupOK = true;
//   }
//   else{
//     Serial.printf("%s\n", config.signer.signupError.message.c_str()); //ถ้าการเชื่อมต่อไม่สำเร็จให้แสดงข้อความตามที่ helper ของ firebase ได้ทำการตั้งค่าเอาไว้ (เราไม่ต้องพิมพ์เอง ให้ระบบเจ็นข้อมูลมาแสดง)
//   }

//   config.token_status_callback = tokenStatusCallback; //ทำการตรวจสอบสอบ Token ระหว่างไมโครคอนโทรเลอร์และตัวไฟล์เบส
//   Firebase.begin(&config, &auth); //เริ่มต้นการทำงานไฟล์เบส โดยใช้้ข้อมูล config และ Authentication ที่ได้ทำการสร้างจากข้างบน
//   Firebase.reconnectWiFi(true); //ตรวจสอบสถานะการทำงานของไวไฟที่ใช้เชื่อมต่อไฟล์เบส
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(Firebase.ready() && signupOK && (millis() - sendDataPreMillis > 5000 || sendDataPreMillis == 0)){ //ตรวจสอบว่าไฟล์เบสพร้อมทำงานหรือยัง และ การ signup เรียบร้อยแล้ว โดยจะทำการทำงานลูปในวงเล็บข้างล่างทุก ๆ 5 วินาทีผ่านฟังก์ชั่น millis()
//     sendDataPreMillis = millis();
    
//     analogData = analogRead(ANA_PIN); //การอ่านค่าแอนาล็อกจากขา A0 มาเก็บไว้ที่ตัวแปร analogData
//     voltage = (float)analogReadMilliVolts(ANA_PIN)/1000; //ทำการแปลงค่าจากอินพุตแอนาล็อกที่ขา A0 ให้เป็นค่าแรงดันไฟฟ้าโดยใช้ฟังก์ชั่น analogReadMilliVolts() หน่วยที่ได้เป็นมิลลิโวลต์จึงต้องเอา 1000 ไปหาร แล้วเอามาเก็บไว้ที่ตัวแปร voltage 
//     state = digitalRead(PIR_PIN); //***รับค่า Boolean มาจากเซ็นเซอร์ PIR ที่ขา 6

//     // การส่งข้อมูลแบบ Integer ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setInt(&fbdo, "Sensor/ana_data", analogData)){ //ทำการตรวจสอบค่า analogData ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/ana_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(analogData); //พิมพ์ค่าตัวแปร analogData
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การส่งข้อมูลแบบ Floating ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setFloat(&fbdo, "Sensor/voltage", voltage)){ //ทำการตรวจสอบค่า voltage ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/voltage
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(voltage); //พิมพ์ค่าตัวแปร voltage
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // *** การส่งข้อมูลแบบ Boolean ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setInt(&fbdo, "Sensor/pir_data", state)){ //ทำการตรวจสอบค่า state ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/pir_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(state); //พิมพ์ค่าตัวแปร state
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//      // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ PWM (แอนาล็อกเสมือน)
//     if(Firebase.RTDB.getInt(&fbdo, "/LED/analog")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/analog
//       if(fbdo.dataType()=="int"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ int หรือไม่
//         pwmValue = fbdo.intData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร pwmValue
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + pwmValue + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         analogWrite(PWM_PIN, pwmValue); //นำค่าที่ได้ไปขับแอนาล็อกเอาต์พุต (PWM) ที่ขา 4
//         delay(100); //ดีเลย์การขับ PWM ที่ขา 4 อยู่ที่ 100 ไมโครวินาที
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปร boolean เพื่อขับการติดและดับของ LED ที่ขา 5
//     if(Firebase.RTDB.getBool(&fbdo, "/LED/digital")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/digital
//       if(fbdo.dataType()=="boolean"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ boolean หรือไม่
//         ledStatus = fbdo.boolData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร ledStatus
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + ledStatus + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         digitalWrite(LEDdigital, ledStatus); //นำค่าที่ได้ไปขับดิจิตอลเอาต์พุตที่ขา 5
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }
//   }
// }



//Episode 14 ตอนที่ 7 การส่งค่า String (ข้อความ) ไปยัง Firebase (Read)
// #include <WiFi.h> //ไลบารี่ไวไฟ
// #include <Firebase_ESP_Client.h> //ไลบารี่ไฟล์เบส
// #include "addons/TokenHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อสร้างโทเคน
// #include "addons/RTDBHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อเพย์โหลดเก็บข้อมูล (Printing) ลงในดาต้าเบสแบบเรียล์ไทม์ (Realtime Database: RTDB) และการช่วยเหลืออื่น ๆ

// #define WIFI_SSID "PY" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "12345678" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

// #define API_KEY "AIzaSyANfLhwcWr4tJ6yup682_RuSdaW8ehU3-g" //ค่า Web API Key ที่ได้จากการสร้างบนไฟล์เบส
// #define DATABASE_URL "https://dontreefirebase-default-rtdb.asia-southeast1.firebasedatabase.app/" //ลิงค์ URL ของดาต้าเบส ได้จากการสร้างบนไฟล์เบส

// // #define LED1_PIN 2 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 2
// // #define LED2_PIN 3 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 3
// #define ANA_PIN A0 //กำหนดขาอินพุตที่เป็นแอนาล็อกไว้ที่ขา A0

// #define PWM_PIN 4 //** กำหนดการใช้งานขา Pulse Width Modulation เอาไว้ที่ขา 4 เป็นอินพุต
// #define LEDdigital 5 //** กำหนดการใช้งานขาเอาต์พุตดิจิตอลที่ต่อออกขา 5
// #define PIR_PIN 6 //*** กำหนดการใช้งานขาอินพุตดิจิตอลที่ต่อเข้าขา 6 ของ PIR Sensor

// FirebaseData fbdo; //สร้างอ็อปเจ็คที่ชื่อว่า fbdo (FireBase Data Output)สำหรับค่าเอาต์พุตดาต้าที่ไมโครเมื่อมีการเปลี่ยนแปลงค่าที่เซ็นเซอร์
// FirebaseAuth auth; //สร้างอ็อปเจ็คที่ชื่อว่า auth (Firebase Authentication) เพื่อใช้สำหรับการยืนยันตัวตนในกรณีที่เข้าใช้งาน Firebase
// FirebaseConfig config; //สร้างอ็อปเจ็คที่ชื่อว่า config เพื่อใช้สำหรับการตั้งค่าต่าง ๆ ระหว่างไมโครคอนโทรเลอร์และไฟล์เบส

// unsigned long sendDataPreMillis = 0; //สร้างตัวแปรชนิด unsigned long เพื่อใช้กับฟังก์ชั่น millis() สำหรับการส่งข้อมูลไปกลับระหว่างไมโครคอนโทรเลอร์และไฟล์เบส
// boolean signupOK = false; //ตัวแปรแบบ bool ใช้เพื่อเก็บค่าการ sing up ของไฟล์เบสว่าสำเร็จหรือไม่ ถ้าสำเร็จให้เก็บค่า 1 ถ้าไม่สำเร็จให้เก็บค่า 0
// int analogData = 0; //ตัวแปรแบบ int ใช้เก็บข้อมูลขาแอนาล็อกที่ขา A0 โดยมีค่าระหว่าง 0 ถึง 4095
// float voltage = 0.0; //ตัวแปรแบบ float ใช้เพื่อแปลงค่า analogData ให้เป็นค่าแรงดันไฟฟ้าที่ป้อนเข้ามาที่ขา A0

// int pwmValue = 0; //** ตัวแปรแบบ PWM ที่ใช้ขับออกที่ขา 4 0-255
// bool ledStatus  = false; //** ตัวแปรขับ LED ที่ขาดิจิตอลที่ขา 5 โดยกำหนดให้เป็นดับก่อน (0)
// bool state = false; //*** ตัวแปรใช้รับค่า PIR Sensor ที่ขาดิจิตอลที่ขา 6 โดยกำหนดให้เป็น 0 ก่อน (0)
// String myString = "No one!"; //**** ตัวแปรส่งค่าที่เป็นข้อความจาก PIR Sensor ที่ขาดิจิตอลที่ขา 6 โดยกำหนดให้เป็น No one! ก่อน


// void setup() {
//   Serial.begin(9600); //กำหนดอัตราบอร์ดเรตสำหรับติดต่อกับ Serial Monitor อยู่ที่ 115200 บิตต่อวินาที
//   pinMode(PWM_PIN, OUTPUT); //** กำหนดให้ขาเอาต์พุต PWM ไว้ที่ขา 4
//   pinMode(LEDdigital, OUTPUT); //** กำหนดให้ขาเอาต์พุตดิจิตอลไว้ที่ขา 5
//   pinMode(PIR_PIN, INPUT); //*** กำหนดให้ขาอินพุตดิจิตอลไว้ที่ขา 6
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //สั่งให้ไวไฟทำงาน โดยอ้างอิงชื่อเราเตอร์และพาสเวิร์ดจาก WIFI_SSID และ WIFI_PASSWORD ที่สร้างจากข้างบน
//   Serial.print("กำลังเชื่อมต่อไวไฟ..."); //แสดงข้อความขณะกำลังเชื่อมต่อไวไฟ
//   while(WiFi.status() != WL_CONNECTED){ // ทำการตรวจสอบการเชื่อมต่อไวไฟว่าเชื่อมต่อแล้วหรือยัง ถ้ายังให้ทำงานในเงื่อนไขข้างล่างในวงเล็บ แต่ถ้าเชื่อมต่อสำเร็จก็ให้หลุดลูปไป
//     Serial.print("."); //พิมพ์จุดไป 1 จุด
//     delay(300); //ดีเลย์ไป 300 มิลลิวินาที
//   }
//   Serial.println(); //ขึ้นบรรทัดใหม่
//   Serial.print("เชื่อมต่อไวไฟสำเร็จ และมีเบอร์ IP คือ "); //แสดงข้อความเมื่อเชื่อมต่อไวไฟสำเร็จ
//   Serial.println(WiFi.localIP()); //แสดงเบอร์ไอพีแอดเดรสของไมโครที่เชื่อมต่อกับเราเตอร์
//   Serial.println(); //ขึ้นบรรทัดใหม่

//   config.api_key = API_KEY; //กำหนดค่า API KEY เพื่อใช้เชื่อมต่อกับไฟล์เบส
//   config.database_url = DATABASE_URL; //กำหนดค่า DATABASE URL เพื่อใช้เชื่อมต่อกับไฟล์เบส

//   if(Firebase.signUp(&config, &auth, "", "")){ //คำสั่ง sign up บนไฟล์เบส โดยให้เอาค่าที่ได้จาก config ข้างบนและ Authentication มาทำการ sign up ในฐานะ anonymous (บุคคลที่ไร้ตัวตน) ใส่เครื่องหมาย "" ทั้งสองตัว โดยทุกครั้งที่ไมโครคอนโทรเลอร์ทำการเชื่อมต่อไปที่ไฟล์เบส จะทำการสร้างยูสเซอร์ใหม่ที่เป็น anonymous ทุกครั้งไป
//     Serial.println("ทำการเชื่อมต่อไฟล์เบสสำเร็จในฐานะ Anonymous"); //แสดงข้อความในกรณีที่ sign up สำเร็จ
//     signupOK = true;
//   }
//   else{
//     Serial.printf("%s\n", config.signer.signupError.message.c_str()); //ถ้าการเชื่อมต่อไม่สำเร็จให้แสดงข้อความตามที่ helper ของ firebase ได้ทำการตั้งค่าเอาไว้ (เราไม่ต้องพิมพ์เอง ให้ระบบเจ็นข้อมูลมาแสดง)
//   }

//   config.token_status_callback = tokenStatusCallback; //ทำการตรวจสอบสอบ Token ระหว่างไมโครคอนโทรเลอร์และตัวไฟล์เบส
//   Firebase.begin(&config, &auth); //เริ่มต้นการทำงานไฟล์เบส โดยใช้้ข้อมูล config และ Authentication ที่ได้ทำการสร้างจากข้างบน
//   Firebase.reconnectWiFi(true); //ตรวจสอบสถานะการทำงานของไวไฟที่ใช้เชื่อมต่อไฟล์เบส
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(Firebase.ready() && signupOK && (millis() - sendDataPreMillis > 5000 || sendDataPreMillis == 0)){ //ตรวจสอบว่าไฟล์เบสพร้อมทำงานหรือยัง และ การ signup เรียบร้อยแล้ว โดยจะทำการทำงานลูปในวงเล็บข้างล่างทุก ๆ 5 วินาทีผ่านฟังก์ชั่น millis()
//     sendDataPreMillis = millis();
    
//     analogData = analogRead(ANA_PIN); //การอ่านค่าแอนาล็อกจากขา A0 มาเก็บไว้ที่ตัวแปร analogData
//     voltage = (float)analogReadMilliVolts(ANA_PIN)/1000; //ทำการแปลงค่าจากอินพุตแอนาล็อกที่ขา A0 ให้เป็นค่าแรงดันไฟฟ้าโดยใช้ฟังก์ชั่น analogReadMilliVolts() หน่วยที่ได้เป็นมิลลิโวลต์จึงต้องเอา 1000 ไปหาร แล้วเอามาเก็บไว้ที่ตัวแปร voltage 
//     state = digitalRead(PIR_PIN); //***รับค่า Boolean มาจากเซ็นเซอร์ PIR ที่ขา 6

//     if(state == 1){
//       myString = "There is an intruder!!!";
//     }
//     else if (state == 0){
//       myString = "No one!";
//     }

//     // การส่งข้อมูลแบบ Integer ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setInt(&fbdo, "Sensor/ana_data", analogData)){ //ทำการตรวจสอบค่า analogData ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/ana_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(analogData); //พิมพ์ค่าตัวแปร analogData
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การส่งข้อมูลแบบ Floating ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setFloat(&fbdo, "Sensor/voltage", voltage)){ //ทำการตรวจสอบค่า voltage ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/voltage
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(voltage); //พิมพ์ค่าตัวแปร voltage
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // *** การส่งข้อมูลแบบ Boolean ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setBool(&fbdo, "Sensor/pir_data", state)){ //ทำการตรวจสอบค่า state ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/pir_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(state); //พิมพ์ค่าตัวแปร state
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // **** การส่งข้อมูลแบบ String ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setString(&fbdo, "Sensor/pir_string", myString)){ //ทำการตรวจสอบค่า myString ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/pir_string
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(myString); //พิมพ์ค่าตัวแปร myString
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//      // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ PWM (แอนาล็อกเสมือน)
//     if(Firebase.RTDB.getInt(&fbdo, "/LED/analog")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/analog
//       if(fbdo.dataType()=="int"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ int หรือไม่
//         pwmValue = fbdo.intData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร pwmValue
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + pwmValue + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         analogWrite(PWM_PIN, pwmValue); //นำค่าที่ได้ไปขับแอนาล็อกเอาต์พุต (PWM) ที่ขา 4
//         delay(100); //ดีเลย์การขับ PWM ที่ขา 4 อยู่ที่ 100 ไมโครวินาที
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปร boolean เพื่อขับการติดและดับของ LED ที่ขา 5
//     if(Firebase.RTDB.getBool(&fbdo, "/LED/digital")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/digital
//       if(fbdo.dataType()=="boolean"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ boolean หรือไม่
//         ledStatus = fbdo.boolData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร ledStatus
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + ledStatus + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         digitalWrite(LEDdigital, ledStatus); //นำค่าที่ได้ไปขับดิจิตอลเอาต์พุตที่ขา 5
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }
//   }
// }




//Episode 14 ตอนที่ 8 การรับค่า String (ข้อความ) มาจาก Firebase (Write)
// #include <WiFi.h> //ไลบารี่ไวไฟ
// #include <Firebase_ESP_Client.h> //ไลบารี่ไฟล์เบส
// #include "addons/TokenHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อสร้างโทเคน
// #include "addons/RTDBHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อเพย์โหลดเก็บข้อมูล (Printing) ลงในดาต้าเบสแบบเรียล์ไทม์ (Realtime Database: RTDB) และการช่วยเหลืออื่น ๆ

// #define WIFI_SSID "PY" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "12345678" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

// #define API_KEY "AIzaSyANfLhwcWr4tJ6yup682_RuSdaW8ehU3-g" //ค่า Web API Key ที่ได้จากการสร้างบนไฟล์เบส
// #define DATABASE_URL "https://dontreefirebase-default-rtdb.asia-southeast1.firebasedatabase.app/" //ลิงค์ URL ของดาต้าเบส ได้จากการสร้างบนไฟล์เบส

// // #define LED1_PIN 2 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 2
// // #define LED2_PIN 3 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 3
// #define ANA_PIN A0 //กำหนดขาอินพุตที่เป็นแอนาล็อกไว้ที่ขา A0

// #define PWM_PIN 4 //** กำหนดการใช้งานขา Pulse Width Modulation เอาไว้ที่ขา 4 เป็นอินพุต
// #define LEDdigital 5 //** กำหนดการใช้งานขาเอาต์พุตดิจิตอลที่ต่อออกขา 5
// #define PIR_PIN 6 //*** กำหนดการใช้งานขาอินพุตดิจิตอลที่ต่อเข้าขา 6 ของ PIR Sensor

// FirebaseData fbdo; //สร้างอ็อปเจ็คที่ชื่อว่า fbdo (FireBase Data Output)สำหรับค่าเอาต์พุตดาต้าที่ไมโครเมื่อมีการเปลี่ยนแปลงค่าที่เซ็นเซอร์
// FirebaseAuth auth; //สร้างอ็อปเจ็คที่ชื่อว่า auth (Firebase Authentication) เพื่อใช้สำหรับการยืนยันตัวตนในกรณีที่เข้าใช้งาน Firebase
// FirebaseConfig config; //สร้างอ็อปเจ็คที่ชื่อว่า config เพื่อใช้สำหรับการตั้งค่าต่าง ๆ ระหว่างไมโครคอนโทรเลอร์และไฟล์เบส

// unsigned long sendDataPreMillis = 0; //สร้างตัวแปรชนิด unsigned long เพื่อใช้กับฟังก์ชั่น millis() สำหรับการส่งข้อมูลไปกลับระหว่างไมโครคอนโทรเลอร์และไฟล์เบส
// boolean signupOK = false; //ตัวแปรแบบ bool ใช้เพื่อเก็บค่าการ sing up ของไฟล์เบสว่าสำเร็จหรือไม่ ถ้าสำเร็จให้เก็บค่า 1 ถ้าไม่สำเร็จให้เก็บค่า 0
// int analogData = 0; //ตัวแปรแบบ int ใช้เก็บข้อมูลขาแอนาล็อกที่ขา A0 โดยมีค่าระหว่าง 0 ถึง 4095
// float voltage = 0.0; //ตัวแปรแบบ float ใช้เพื่อแปลงค่า analogData ให้เป็นค่าแรงดันไฟฟ้าที่ป้อนเข้ามาที่ขา A0

// int pwmValue = 0; //** ตัวแปรแบบ PWM ที่ใช้ขับออกที่ขา 4 0-255
// bool ledStatus  = false; //** ตัวแปรขับ LED ที่ขาดิจิตอลที่ขา 5 โดยกำหนดให้เป็นดับก่อน (0)
// bool state = false; //*** ตัวแปรใช้รับค่า PIR Sensor ที่ขาดิจิตอลที่ขา 6 โดยกำหนดให้เป็น 0 ก่อน (0)
// String myString = "No one!"; //**** ตัวแปรส่งค่าที่เป็นข้อความจาก PIR Sensor ที่ขาดิจิตอลที่ขา 6 โดยกำหนดให้เป็น No one! ก่อน
// String fbString = "Hello"; //***** ตัวแปรที่ใช้รับค่าจากไฟล์เบส

// void setup() {
//   Serial.begin(9600); //กำหนดอัตราบอร์ดเรตสำหรับติดต่อกับ Serial Monitor อยู่ที่ 115200 บิตต่อวินาที
//   pinMode(PWM_PIN, OUTPUT); //** กำหนดให้ขาเอาต์พุต PWM ไว้ที่ขา 4
//   pinMode(LEDdigital, OUTPUT); //** กำหนดให้ขาเอาต์พุตดิจิตอลไว้ที่ขา 5
//   pinMode(PIR_PIN, INPUT); //*** กำหนดให้ขาอินพุตดิจิตอลไว้ที่ขา 6
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //สั่งให้ไวไฟทำงาน โดยอ้างอิงชื่อเราเตอร์และพาสเวิร์ดจาก WIFI_SSID และ WIFI_PASSWORD ที่สร้างจากข้างบน
//   Serial.print("กำลังเชื่อมต่อไวไฟ..."); //แสดงข้อความขณะกำลังเชื่อมต่อไวไฟ
//   while(WiFi.status() != WL_CONNECTED){ // ทำการตรวจสอบการเชื่อมต่อไวไฟว่าเชื่อมต่อแล้วหรือยัง ถ้ายังให้ทำงานในเงื่อนไขข้างล่างในวงเล็บ แต่ถ้าเชื่อมต่อสำเร็จก็ให้หลุดลูปไป
//     Serial.print("."); //พิมพ์จุดไป 1 จุด
//     delay(300); //ดีเลย์ไป 300 มิลลิวินาที
//   }
//   Serial.println(); //ขึ้นบรรทัดใหม่
//   Serial.print("เชื่อมต่อไวไฟสำเร็จ และมีเบอร์ IP คือ "); //แสดงข้อความเมื่อเชื่อมต่อไวไฟสำเร็จ
//   Serial.println(WiFi.localIP()); //แสดงเบอร์ไอพีแอดเดรสของไมโครที่เชื่อมต่อกับเราเตอร์
//   Serial.println(); //ขึ้นบรรทัดใหม่

//   config.api_key = API_KEY; //กำหนดค่า API KEY เพื่อใช้เชื่อมต่อกับไฟล์เบส
//   config.database_url = DATABASE_URL; //กำหนดค่า DATABASE URL เพื่อใช้เชื่อมต่อกับไฟล์เบส

//   if(Firebase.signUp(&config, &auth, "", "")){ //คำสั่ง sign up บนไฟล์เบส โดยให้เอาค่าที่ได้จาก config ข้างบนและ Authentication มาทำการ sign up ในฐานะ anonymous (บุคคลที่ไร้ตัวตน) ใส่เครื่องหมาย "" ทั้งสองตัว โดยทุกครั้งที่ไมโครคอนโทรเลอร์ทำการเชื่อมต่อไปที่ไฟล์เบส จะทำการสร้างยูสเซอร์ใหม่ที่เป็น anonymous ทุกครั้งไป
//     Serial.println("ทำการเชื่อมต่อไฟล์เบสสำเร็จในฐานะ Anonymous"); //แสดงข้อความในกรณีที่ sign up สำเร็จ
//     signupOK = true;
//   }
//   else{
//     Serial.printf("%s\n", config.signer.signupError.message.c_str()); //ถ้าการเชื่อมต่อไม่สำเร็จให้แสดงข้อความตามที่ helper ของ firebase ได้ทำการตั้งค่าเอาไว้ (เราไม่ต้องพิมพ์เอง ให้ระบบเจ็นข้อมูลมาแสดง)
//   }

//   config.token_status_callback = tokenStatusCallback; //ทำการตรวจสอบสอบ Token ระหว่างไมโครคอนโทรเลอร์และตัวไฟล์เบส
//   Firebase.begin(&config, &auth); //เริ่มต้นการทำงานไฟล์เบส โดยใช้้ข้อมูล config และ Authentication ที่ได้ทำการสร้างจากข้างบน
//   Firebase.reconnectWiFi(true); //ตรวจสอบสถานะการทำงานของไวไฟที่ใช้เชื่อมต่อไฟล์เบส
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(Firebase.ready() && signupOK && (millis() - sendDataPreMillis > 5000 || sendDataPreMillis == 0)){ //ตรวจสอบว่าไฟล์เบสพร้อมทำงานหรือยัง และ การ signup เรียบร้อยแล้ว โดยจะทำการทำงานลูปในวงเล็บข้างล่างทุก ๆ 5 วินาทีผ่านฟังก์ชั่น millis()
//     sendDataPreMillis = millis();
    
//     analogData = analogRead(ANA_PIN); //การอ่านค่าแอนาล็อกจากขา A0 มาเก็บไว้ที่ตัวแปร analogData
//     voltage = (float)analogReadMilliVolts(ANA_PIN)/1000; //ทำการแปลงค่าจากอินพุตแอนาล็อกที่ขา A0 ให้เป็นค่าแรงดันไฟฟ้าโดยใช้ฟังก์ชั่น analogReadMilliVolts() หน่วยที่ได้เป็นมิลลิโวลต์จึงต้องเอา 1000 ไปหาร แล้วเอามาเก็บไว้ที่ตัวแปร voltage 
//     state = digitalRead(PIR_PIN); //***รับค่า Boolean มาจากเซ็นเซอร์ PIR ที่ขา 6

//     if(state == 1){
//       myString = "There is an intruder!!!";
//     }
//     else if (state == 0){
//       myString = "No one!";
//     }

//     // การส่งข้อมูลแบบ Integer ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setInt(&fbdo, "Sensor/ana_data", analogData)){ //ทำการตรวจสอบค่า analogData ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/ana_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(analogData); //พิมพ์ค่าตัวแปร analogData
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การส่งข้อมูลแบบ Floating ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setFloat(&fbdo, "Sensor/voltage", voltage)){ //ทำการตรวจสอบค่า voltage ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/voltage
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(voltage); //พิมพ์ค่าตัวแปร voltage
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // *** การส่งข้อมูลแบบ Boolean ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setBool(&fbdo, "Sensor/pir_data", state)){ //ทำการตรวจสอบค่า state ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/pir_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(state); //พิมพ์ค่าตัวแปร state
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // **** การส่งข้อมูลแบบ String ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setString(&fbdo, "Sensor/pir_string", myString)){ //ทำการตรวจสอบค่า myString ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/pir_string
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(myString); //พิมพ์ค่าตัวแปร myString
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//      // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ PWM (แอนาล็อกเสมือน)
//     if(Firebase.RTDB.getInt(&fbdo, "/LED/analog")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/analog
//       if(fbdo.dataType()=="int"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ int หรือไม่
//         pwmValue = fbdo.intData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร pwmValue
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + pwmValue + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         analogWrite(PWM_PIN, pwmValue); //นำค่าที่ได้ไปขับแอนาล็อกเอาต์พุต (PWM) ที่ขา 4
//         delay(100); //ดีเลย์การขับ PWM ที่ขา 4 อยู่ที่ 100 ไมโครวินาที
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปร boolean เพื่อขับการติดและดับของ LED ที่ขา 5
//     if(Firebase.RTDB.getBool(&fbdo, "/LED/digital")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/digital
//       if(fbdo.dataType()=="boolean"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ boolean หรือไม่
//         ledStatus = fbdo.boolData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร ledStatus
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + ledStatus + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         digitalWrite(LEDdigital, ledStatus); //นำค่าที่ได้ไปขับดิจิตอลเอาต์พุตที่ขา 5
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // ***** การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ String
//     if(Firebase.RTDB.getString(&fbdo, "/LED/string")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/string
//       if(fbdo.dataType()=="string"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ String หรือไม่
//         fbString = fbdo.stringData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร fbString
//         Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + fbString + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
//         Serial.println(fbString); //นำค่าที่รับได้มาแสดงผล
//       }
//     }
//     else{
//       Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }
//   }
// }





//Episode 14 ตอนที่ 9 การรับค่า Float (ตัวเลขทศนิยม) มาจาก Firebase (Write)
#include <WiFi.h> //ไลบารี่ไวไฟ
#include <Firebase_ESP_Client.h> //ไลบารี่ไฟล์เบส
#include "addons/TokenHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อสร้างโทเคน
#include "addons/RTDBHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อเพย์โหลดเก็บข้อมูล (Printing) ลงในดาต้าเบสแบบเรียล์ไทม์ (Realtime Database: RTDB) และการช่วยเหลืออื่น ๆ

// #define WIFI_SSID "@KM_Apartment4" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "km99956000" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

// #define WIFI_SSID "JimJumZz" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "77777777" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

#define WIFI_SSID "PY" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
#define WIFI_PASSWORD "12345678" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

#define API_KEY "AIzaSyANfLhwcWr4tJ6yup682_RuSdaW8ehU3-g" //ค่า Web API Key ที่ได้จากการสร้างบนไฟล์เบส
#define DATABASE_URL "https://dontreefirebase-default-rtdb.asia-southeast1.firebasedatabase.app/" //ลิงค์ URL ของดาต้าเบส ได้จากการสร้างบนไฟล์เบส

// #define LED1_PIN 2 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 2
// #define LED2_PIN 3 //** กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 3
#define ANA_PIN A0 //กำหนดขาอินพุตที่เป็นแอนาล็อกไว้ที่ขา A0

#define PWM_PIN 4 //** กำหนดการใช้งานขา Pulse Width Modulation เอาไว้ที่ขา 4 เป็นอินพุต
#define LEDdigital 5 //** กำหนดการใช้งานขาเอาต์พุตดิจิตอลที่ต่อออกขา 5
#define PIR_PIN 6 //*** กำหนดการใช้งานขาอินพุตดิจิตอลที่ต่อเข้าขา 6 ของ PIR Sensor

FirebaseData fbdo; //สร้างอ็อปเจ็คที่ชื่อว่า fbdo (FireBase Data Output)สำหรับค่าเอาต์พุตดาต้าที่ไมโครเมื่อมีการเปลี่ยนแปลงค่าที่เซ็นเซอร์
FirebaseAuth auth; //สร้างอ็อปเจ็คที่ชื่อว่า auth (Firebase Authentication) เพื่อใช้สำหรับการยืนยันตัวตนในกรณีที่เข้าใช้งาน Firebase
FirebaseConfig config; //สร้างอ็อปเจ็คที่ชื่อว่า config เพื่อใช้สำหรับการตั้งค่าต่าง ๆ ระหว่างไมโครคอนโทรเลอร์และไฟล์เบส

unsigned long sendDataPreMillis = 0; //สร้างตัวแปรชนิด unsigned long เพื่อใช้กับฟังก์ชั่น millis() สำหรับการส่งข้อมูลไปกลับระหว่างไมโครคอนโทรเลอร์และไฟล์เบส
boolean signupOK = false; //ตัวแปรแบบ bool ใช้เพื่อเก็บค่าการ sing up ของไฟล์เบสว่าสำเร็จหรือไม่ ถ้าสำเร็จให้เก็บค่า 1 ถ้าไม่สำเร็จให้เก็บค่า 0
int analogData = 0; //ตัวแปรแบบ int ใช้เก็บข้อมูลขาแอนาล็อกที่ขา A0 โดยมีค่าระหว่าง 0 ถึง 4095
float voltage = 0.0; //ตัวแปรแบบ float ใช้เพื่อแปลงค่า analogData ให้เป็นค่าแรงดันไฟฟ้าที่ป้อนเข้ามาที่ขา A0

int pwmValue = 0; //** ตัวแปรแบบ PWM ที่ใช้ขับออกที่ขา 4 0-255
bool ledStatus  = false; //** ตัวแปรขับ LED ที่ขาดิจิตอลที่ขา 5 โดยกำหนดให้เป็นดับก่อน (0)
bool state = false; //*** ตัวแปรใช้รับค่า PIR Sensor ที่ขาดิจิตอลที่ขา 6 โดยกำหนดให้เป็น 0 ก่อน (0)
String myString = "No one!"; //**** ตัวแปรส่งค่าที่เป็นข้อความจาก PIR Sensor ที่ขาดิจิตอลที่ขา 6 โดยกำหนดให้เป็น No one! ก่อน
String fbString = "Hello"; //***** ตัวแปรที่ใช้รับค่าจากไฟล์เบสที่เป็นข้อความ
float fbFloat = 2.2; //****** ตัวแปรที่ใช้รับค่าจากไฟล์เบสที่เป็นตัวเลขที่มีจุดทศนิยม

void setup() {
  Serial.begin(9600); //กำหนดอัตราบอร์ดเรตสำหรับติดต่อกับ Serial Monitor อยู่ที่ 115200 บิตต่อวินาที
  pinMode(PWM_PIN, OUTPUT); //** กำหนดให้ขาเอาต์พุต PWM ไว้ที่ขา 4
  pinMode(LEDdigital, OUTPUT); //** กำหนดให้ขาเอาต์พุตดิจิตอลไว้ที่ขา 5
  pinMode(PIR_PIN, INPUT); //*** กำหนดให้ขาอินพุตดิจิตอลไว้ที่ขา 6
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //สั่งให้ไวไฟทำงาน โดยอ้างอิงชื่อเราเตอร์และพาสเวิร์ดจาก WIFI_SSID และ WIFI_PASSWORD ที่สร้างจากข้างบน
  Serial.print("กำลังเชื่อมต่อไวไฟ..."); //แสดงข้อความขณะกำลังเชื่อมต่อไวไฟ
  while(WiFi.status() != WL_CONNECTED){ // ทำการตรวจสอบการเชื่อมต่อไวไฟว่าเชื่อมต่อแล้วหรือยัง ถ้ายังให้ทำงานในเงื่อนไขข้างล่างในวงเล็บ แต่ถ้าเชื่อมต่อสำเร็จก็ให้หลุดลูปไป
    Serial.print("."); //พิมพ์จุดไป 1 จุด
    delay(300); //ดีเลย์ไป 300 มิลลิวินาที
  }
  Serial.println(); //ขึ้นบรรทัดใหม่
  Serial.print("เชื่อมต่อไวไฟสำเร็จ และมีเบอร์ IP คือ "); //แสดงข้อความเมื่อเชื่อมต่อไวไฟสำเร็จ
  Serial.println(WiFi.localIP()); //แสดงเบอร์ไอพีแอดเดรสของไมโครที่เชื่อมต่อกับเราเตอร์
  Serial.println(); //ขึ้นบรรทัดใหม่

  config.api_key = API_KEY; //กำหนดค่า API KEY เพื่อใช้เชื่อมต่อกับไฟล์เบส
  config.database_url = DATABASE_URL; //กำหนดค่า DATABASE URL เพื่อใช้เชื่อมต่อกับไฟล์เบส

  if(Firebase.signUp(&config, &auth, "", "")){ //คำสั่ง sign up บนไฟล์เบส โดยให้เอาค่าที่ได้จาก config ข้างบนและ Authentication มาทำการ sign up ในฐานะ anonymous (บุคคลที่ไร้ตัวตน) ใส่เครื่องหมาย "" ทั้งสองตัว โดยทุกครั้งที่ไมโครคอนโทรเลอร์ทำการเชื่อมต่อไปที่ไฟล์เบส จะทำการสร้างยูสเซอร์ใหม่ที่เป็น anonymous ทุกครั้งไป
    Serial.println("ทำการเชื่อมต่อไฟล์เบสสำเร็จในฐานะ Anonymous"); //แสดงข้อความในกรณีที่ sign up สำเร็จ
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str()); //ถ้าการเชื่อมต่อไม่สำเร็จให้แสดงข้อความตามที่ helper ของ firebase ได้ทำการตั้งค่าเอาไว้ (เราไม่ต้องพิมพ์เอง ให้ระบบเจ็นข้อมูลมาแสดง)
  }

  config.token_status_callback = tokenStatusCallback; //ทำการตรวจสอบสอบ Token ระหว่างไมโครคอนโทรเลอร์และตัวไฟล์เบส
  Firebase.begin(&config, &auth); //เริ่มต้นการทำงานไฟล์เบส โดยใช้้ข้อมูล config และ Authentication ที่ได้ทำการสร้างจากข้างบน
  Firebase.reconnectWiFi(true); //ตรวจสอบสถานะการทำงานของไวไฟที่ใช้เชื่อมต่อไฟล์เบส
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Firebase.ready() && signupOK && (millis() - sendDataPreMillis > 5000 || sendDataPreMillis == 0)){ //ตรวจสอบว่าไฟล์เบสพร้อมทำงานหรือยัง และ การ signup เรียบร้อยแล้ว โดยจะทำการทำงานลูปในวงเล็บข้างล่างทุก ๆ 5 วินาทีผ่านฟังก์ชั่น millis()
    sendDataPreMillis = millis();
    
    analogData = analogRead(ANA_PIN); //การอ่านค่าแอนาล็อกจากขา A0 มาเก็บไว้ที่ตัวแปร analogData
    voltage = (float)analogReadMilliVolts(ANA_PIN)/1000; //ทำการแปลงค่าจากอินพุตแอนาล็อกที่ขา A0 ให้เป็นค่าแรงดันไฟฟ้าโดยใช้ฟังก์ชั่น analogReadMilliVolts() หน่วยที่ได้เป็นมิลลิโวลต์จึงต้องเอา 1000 ไปหาร แล้วเอามาเก็บไว้ที่ตัวแปร voltage 
    state = digitalRead(PIR_PIN); //***รับค่า Boolean มาจากเซ็นเซอร์ PIR ที่ขา 6

    if(state == 1){
      myString = "There is an intruder!!!";
    }
    else if (state == 0){
      myString = "No one!";
    }

    // การส่งข้อมูลแบบ Integer ไปเก็บไว้บนไฟล์เบส
    if(Firebase.RTDB.setInt(&fbdo, "Sensor/ana_data", analogData)){ //ทำการตรวจสอบค่า analogData ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/ana_data
      Serial.println(); //ขึ้นบรรทัดใหม่
      Serial.print(analogData); //พิมพ์ค่าตัวแปร analogData
      Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
      Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
    }
    else{
      Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }

    // การส่งข้อมูลแบบ Floating ไปเก็บไว้บนไฟล์เบส
    if(Firebase.RTDB.setFloat(&fbdo, "Sensor/voltage", voltage)){ //ทำการตรวจสอบค่า voltage ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/voltage
      Serial.println(); //ขึ้นบรรทัดใหม่
      Serial.print(voltage); //พิมพ์ค่าตัวแปร voltage
      Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
      Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
    }
    else{
      Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }

    // *** การส่งข้อมูลแบบ Boolean ไปเก็บไว้บนไฟล์เบส
    if(Firebase.RTDB.setBool(&fbdo, "Sensor/pir_data", state)){ //ทำการตรวจสอบค่า state ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/pir_data
      Serial.println(); //ขึ้นบรรทัดใหม่
      Serial.print(state); //พิมพ์ค่าตัวแปร state
      Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
      Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
    }
    else{
      Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }

    // **** การส่งข้อมูลแบบ String ไปเก็บไว้บนไฟล์เบส
    if(Firebase.RTDB.setString(&fbdo, "Sensor/pir_string", myString)){ //ทำการตรวจสอบค่า myString ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/pir_string
      Serial.println(); //ขึ้นบรรทัดใหม่
      Serial.print(myString); //พิมพ์ค่าตัวแปร myString
      Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
      Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
    }
    else{
      Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }

     // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ PWM (แอนาล็อกเสมือน)
    if(Firebase.RTDB.getInt(&fbdo, "/LED/analog")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/analog
      if(fbdo.dataType()=="int"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ int หรือไม่
        pwmValue = fbdo.intData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร pwmValue
        Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + pwmValue + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
        analogWrite(PWM_PIN, pwmValue); //นำค่าที่ได้ไปขับแอนาล็อกเอาต์พุต (PWM) ที่ขา 4
        delay(100); //ดีเลย์การขับ PWM ที่ขา 4 อยู่ที่ 100 ไมโครวินาที
      }
    }
    else{
      Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }

    // การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปร boolean เพื่อขับการติดและดับของ LED ที่ขา 5
    if(Firebase.RTDB.getBool(&fbdo, "/LED/digital")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/digital
      if(fbdo.dataType()=="boolean"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ boolean หรือไม่
        ledStatus = fbdo.boolData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร ledStatus
        Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + ledStatus + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
        digitalWrite(LEDdigital, ledStatus); //นำค่าที่ได้ไปขับดิจิตอลเอาต์พุตที่ขา 5
      }
    }
    else{
      Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }

    // ***** การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ String
    if(Firebase.RTDB.getString(&fbdo, "/LED/string")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/string
      if(fbdo.dataType()=="string"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ String หรือไม่
        fbString = fbdo.stringData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร fbString
        Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + fbString + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
        Serial.println(fbString); //นำค่าที่รับได้มาแสดงผล
      }
    }
    else{
      Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }

     // ****** การรับข้อมูลจากไฟล์เบสลงมาที่ไมโครคอนโทรเลอร์โดยเป็นตัวแปรแบบ Float
    if(Firebase.RTDB.getFloat(&fbdo, "/LED/float")){ //ทำการตรวจรับค่าจากไดเร็คทอรี่ /LED/float
      if(fbdo.dataType()=="float"){ //ทำการเช็คชนิดของตัวแปรในไฟล์เบสว่าเป็นแบบ Float หรือไม่
        fbFloat = fbdo.floatData(); //นำค่าที่ได้มาเก็บไว้ในตัวแปร fbFloat
        Serial.println("อ่านค่าสำเร็จจาก Firebase ผ่านไดเร็กทอรี่" + fbdo.dataPath() + ": " + fbFloat + "(" + fbdo.dataType() +")"); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบสพร้อมทั้งค่าที่รับได้และชนิดของตัวแปรที่ใช้
        Serial.println(fbFloat); //นำค่าที่รับได้มาแสดงผล
      }
    }
    else{
      Serial.println("การรับข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถรับข้อมูลจากไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
    }
  }
}

