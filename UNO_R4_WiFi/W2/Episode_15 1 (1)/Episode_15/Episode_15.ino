#include <DHT11.h>

//Episode 15 ตอนที่ 1 การส่งข้อมูลจาก Arduino Nano ESP32 ไปเก็บไว้ยัง Google Sheet
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
// #include "DHT.h" //ไลบารี่ของเซ็นเซอร์ DHT

#define DHTTYPE DHT11   // ระบุรุ่นของเซ็นเซอร์ DHT ในที่นี้ใช้เป็น DHT 11
const int DHTPin = 7; // ระบุขาที่ใช้ต่อกับเซ็นเซอร์ DHT11
DHT dht(DHTPin, DHTTYPE);

WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(9600);
    delay(10);
    dht.begin(); 
    // We start by connecting to a WiFi network
    // WiFiMulti.addAP("@KM_Apartment4", "km99956000");
    WiFiMulti.addAP("JimJumZz", "77777777");

    Serial.println();
    Serial.println();
    Serial.print("ทำการเชื่อมต่อไวไฟ... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop()
{
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        float h = dht.readHumidity(); //ความชื้น
        float t = dht.readTemperature(); //อุณหภุมิ

        String url = "https://docs.google.com/spreadsheets/d/16uWdM_EdUcXskTH3J3XW9n9RYtNZcKTqZzDlLcq7a_s/edit?usp=sharing" + String(t) + "&humi=" + String(h);
        Serial.println("ทำการส่งค่าขึ้นไปยัง Google Sheet...");
        http.begin(url.c_str()); //Specify the URL and certificate
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        int httpCode = http.GET();
        String payload;
        if (httpCode > 0) { //Check for the returning code
          payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
        }
        else {
          Serial.println("การส่งผิดพลาดและล้มเหลว");
        }
        http.end();
      }


    Serial.println("ทำการรอ 2 วินาทีเพื่อที่จะทำการส่งใหม่...");
    delay(2000); // ตั้งค่าเวลาลูปสำหรับการส่ง โดยกำหนดให้เป็น 5 วินาที
}




//Episode 15 ตอนที่ 2 แนะนำเว็ปไซต์ตัวอย่างการใช้งาน Arduino Nano ESP32
// #include <WiFi.h> //เรียกใช้งานไลบารี่ไวไฟ
// #include <HTTPClient.h> //เรียกใช้งานไลบารี่ที่ใช้ส่งข้อมูลที่ใช้โปรโตคอล http ในฝั่งไคลเอ็นต์

// //---------------------------------------------------------------------
// const char * ssid = "Nice"; //ชื่อเราเตอร์ที่ใช้
// const char * password = "NICENICE"; //พาสเวิร์ดของเราเตอร์

// String GOOGLE_SCRIPT_ID = "AKfycbwIBSIi2zNxriStQ0ommoVEEO3Ta8aio2gHARc9nwT0Rcx_FzQZS20keiiMgYtc2zOe"; //สคริปไอดีที่ได้จาก Google Sheet
// //---------------------------------------------------------------------

// //-----------------------------
// #define relay1_pin 2 //กำหนดขาอุปกรณ์ที่จะใช้ควบคุมเป็นขาที่ 2 ให้ชื่อว่า relay1_pin
// #define relay2_pin 3 //กำหนดขาอุปกรณ์ที่จะใช้ควบคุมเป็นขาที่ 3 ให้ชื่อว่า relay2_pin
// #define relay3_pin 4 //กำหนดขาอุปกรณ์ที่จะใช้ควบคุมเป็นขาที่ 4 ให้ชื่อว่า relay3_pin
// #define relay4_pin 5 //กำหนดขาอุปกรณ์ที่จะใช้ควบคุมเป็นขาที่ 5 ให้ชื่อว่า relay4_pin
// //-----------------------------

// const int sendInterval = 2000; //ระยะเวลาในการส่งในแต่ละรอบ โดยกำหนดให้ค่าเริ่มต้นเป็น 2 วินาที

// WiFiClientSecure client; //กำหนดให้ไมโครคอนโทรเลอร์เป็นไคลเอ็นต์

// // ส่วนของฟังก์ชั่น setup
// void setup() {
//   //--------------------------------------------
//   pinMode(relay1_pin, OUTPUT); //กำหนดให้ขาที่ 2 เป็นเอาต์พุต
//   pinMode(relay2_pin, OUTPUT); //กำหนดให้ขาที่ 3 เป็นเอาต์พุต
//   pinMode(relay3_pin, OUTPUT); //กำหนดให้ขาที่ 4 เป็นเอาต์พุต
//   pinMode(relay4_pin, OUTPUT); //กำหนดให้ขาที่ 5 เป็นเอาต์พุต
//   //--------------------------------------------
//   Serial.begin(115200); //กำหนดให้อัตราบอร์ดเรตในการสื่อสารข้อมูลใน Serial Monitor มีค่าเท่ากับ 115000 บิตต่อวินาที
//   delay(10); //ดีเลย์ 10 มิลลิวินาที
//   //--------------------------------------------
//   WiFi.mode(WIFI_STA); //กำหนดโหมดของไวไฟที่ใช้ให้เป็นแบบ STA (Station mode หรือ Wi-Fi client mode)
//   WiFi.begin(ssid, password); //สั่งให้ไวไฟทำงานโดยอ้างอิงชื่อและพาสเวิร์ดตามที่ได้กำหนดไว้ตามโค้ดข้างบน

//   Serial.print("กำลังเชื่อมต่อไวไฟ..."); //สั่งพิมพ์ข้อความออก Serial Monitor ในขณะที่กำลังเชื่อมต่อไวไฟ
//   while (WiFi.status() != WL_CONNECTED) { //ขณะที่กำลังเชื่อมต่อไวไฟกับเราต์เตอร์ ให้ทำการพิมพ์ . ในทุก ๆ 300 มิลลิวินาที
//     Serial.print(".");
//     delay(300);
//   }
//   Serial.println("เชื่อมต่อไวไฟสำเร็จ"); //เมื่อเชื่อมต่อไวไฟสำเร็จก็ให้ขึ้นข้อความ
//   Serial.println("IP address: "); //พิมพ์ข้อความ IP address:
//   Serial.println(WiFi.localIP()); //แสดงเบอร์ไอพีแอดเดรสที่ได้รับจากเราต์เตอร์
//   //--------------------------------------------
// }

// //ส่วนของเนื้อโปรแกรมจะเรียกผ่านฟังก์ชั่น read_google_sheet();
// void loop() {
//   read_google_sheet(); // เรียกใช้งานฟังก์ชั่น read_google_sheet();
//   delay(sendInterval); //กำหนดให้รอบในการส่งแต่ละรอบอยู่ที่ 2 วินาที ตามค่าที่ได้ประกาศเอาไว้ข้างบน
// }

// //ฟังก์ชั่นการทำงานหลัก read_google_sheet();
// void read_google_sheet(void) {
//    //-----------------------------------------------------------------------------------
//    HTTPClient http; //ประกาศออปเจ็ค http เพื่อใช้งานคำสั่งที่อยู่ในไลบารี่ HTTPClient.h
//    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read"; //คำสั่งที่ใช้เรียกค่าจาก Google Sheet ในรูปแบบโปรโตคอล http
//   //Serial.print(url);
//   Serial.println("กำลังอ่านค่าจาก Google Sheet....."); //ขณะที่กำลังอ่านค่าจาก Google Sheet ให้แสดงข้อความ กำลังอ่านค่าจาก Google Sheet.....
//   http.begin(url.c_str()); //สั่งให้โปรโตคอล http ทำงาน
//   //-----------------------------------------------------------------------------------
//   //สั่งไม่ให้คำสั่ง Eror ทำงาน ---> "302 Moved Temporarily Error"
//   http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
//   //-----------------------------------------------------------------------------------
//   //ทำการรับค่ารหัสสถานะของโปรโตคอล http (Get the returning HTTP status code)
//   int httpCode = http.GET(); //รับค่ารหัสสถานะของโปรโตคอล http ในสภาวะปกติ รหัสตรงนี้จะมีค่าเป็น 200
//   Serial.print("รหัสสถานะของโปรโตคอล http: "); //แสดงข้อความที่ Serial Monitor
//   Serial.println(httpCode); //แสดงรหัสสถานะของ http
//   //-----------------------------------------------------------------------------------
//   if(httpCode <= 0){Serial.println("มีความผิดพลาดเกิดขึ้นในการเชื่อมต่อโปรโตคอล http"); http.end(); return;} //ในกรณีมีความผิดพลาดเกิดขึ้นในการร้องขอสถานะ http ให้ขึ้นข้อความดังกล่าว
//   //-----------------------------------------------------------------------------------
//   //ทำการอ่านข้อมูลจาก Google sheet
//   String payload = http.getString(); //อ่านค่าจากเพย์โหลดที่ได้จาก Google Sheet
//   Serial.println("Payload: "+payload); //แสดงผลค่าเพย์โหลดที่ได้จาก Google Sheet ใน Serial Monitor
//   //-----------------------------------------------------------------------------------
//   if(httpCode == 200){ //ในกรณีที่เชื่อมต่อกับ Google Sheet ได้ปกติ (รหัสเป็น 200)
//     //=====================================================================
//     //get relay number from payload variable
//     String temp = payload.substring(0, 1);
//     int relay_number = temp.toInt();
//     //=====================================================================
//     //get the command comming from Google Sheet
//     //i.e ON or OFF
//     payload.remove(0, 1);
//     payload.toLowerCase();
//     payload.trim();
//     Serial.println("Payload - Command: "+payload);
//     //=====================================================================
//     if(payload != "on" && payload != "off")
//       {Serial.println("คำสั่งการติด/ดับของอุปกรณ์ผิดพลาด"); http.end(); return;}
//     //=====================================================================
//     if(relay_number < 1 || relay_number > 4) // ในกรณีที่จำนวนอุปกรณ์เชื่อมต่อมากกว่า 4 ตัว ให้มาแก้ค่าตรงนี้
//       {Serial.println("จำนวนอุปกรณ์ไม่อยู่ในค่าที่กำหนด"); http.end(); return;}
//     //=====================================================================
//     int relay_state = control_relay(relay_number, payload);
//     write_google_sheet( "relay_number="+String(relay_number)+"&relay_state="+String(relay_state) );
//     //=====================================================================
//   }
//   //-------------------------------------------------------------------------------------
//   http.end();
// }

// //ฟังก์ชั่นในการเขียนค่าลงใน Google Sheet ในกรณีที่จะส่งสถานะการติดดับให้กับ Google Sheet
// void write_google_sheet(String params) {
//    HTTPClient http;
//    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
//    //Serial.print(url);
//     Serial.println("กำลังอัพเดตสถานะของตัวอุปกรณ์ที่ทำการเชื่อมต่อที่ไมโครคอนโทรเลอร์");
//     http.begin(url.c_str());
//     http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
//     int httpCode = http.GET();  
//     Serial.print("รหัสสถานะของโปรโตคอล http: ");
//     Serial.println(httpCode);
    
//     String payload;
//     if (httpCode > 0) {
//         payload = http.getString(); //อ่านค่าจากเพย์โหลดที่ได้จาก Google Sheet
//         Serial.println("Payload: "+payload);  //แสดงผลค่าเพย์โหลดที่ได้จาก Google Sheet ใน Serial Monitor   
//     }
//     http.end();
// }

// //ส่วนของการควบคุมอุปกรณ์อิเล็กทรอนิกส์ที่ไมโครคอนโทรเลอร์ หากทำการเพิ่มหรือลดตัวอุปกรณ์ที่ต่อกับตัวไมโครคอนโทรเลอร์ ต้องมาแก้ไขในส่วนนี้
// int control_relay(int relay, String command){
//   switch (relay) {
//     //------------------------------------------------
//     case 1:
//       if(command == "on"){
//         digitalWrite(relay1_pin, HIGH);
//         Serial.println("อุปกรณ์ตัวที่ 1 ติด");
//         return 1;
//       } else {
//         digitalWrite(relay1_pin, LOW);
//         Serial.println("อุปกรณ์ตัวที่ 1 ดับ");
//         return 0;
//       }
//       break;
//     //------------------------------------------------
//     case 2:
//       if(command == "on"){
//         digitalWrite(relay2_pin, HIGH);
//         Serial.println("อุปกรณ์ตัวที่ 2 ติด");
//         return 1;
//       } else {
//         digitalWrite(relay2_pin, LOW);
//         Serial.println("อุปกรณ์ตัวที่ 2 ดับ");
//         return 0;
//       }
//       break;
//     //------------------------------------------------
//     case 3:
//       if(command == "on"){
//         digitalWrite(relay3_pin, HIGH);
//         Serial.println("อุปกรณ์ตัวที่ 3 ติด");
//         return 1;
//       } else {
//         digitalWrite(relay3_pin, LOW);
//         Serial.println("อุปกรณ์ตัวที่ 3 ดับ");
//         return 0;
//       }
//       break;
//     //------------------------------------------------
//     case 4:
//       if(command == "on"){
//         digitalWrite(relay4_pin, HIGH);
//         Serial.println("อุปกรณ์ตัวที่ 4 ติด");
//         return 1;
//       } else {
//         digitalWrite(relay4_pin, LOW);
//         Serial.println("อุปกรณ์ตัวที่ 4 ดับ");
//         return 0;
//       }
//       break;
//     //------------------------------------------------    
//     default:
//       return -1;
//       break;
//   }
// }



// //Episode 15 ตอนที่ 4 การลิงค์ค่ากันระหว่าง Google Sheet และ Firebase โดยรับค่าจาก Arduino Nano ESP32
// #include <WiFi.h> //ไลบารี่ไวไฟ
//  #include <Firebase_ESP_Client.h> //ไลบารี่ไฟล์เบส
// #include "addons/TokenHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อสร้างโทเคน
// #include "addons/RTDBHelper.h" // ตัวแอดออน (เพิ่ม) ของไฟล์เบสเพื่อเพย์โหลดเก็บข้อมูล (Printing) ลงในดาต้าเบสแบบเรียล์ไทม์ (Realtime Database: RTDB) และการช่วยเหลืออื่น ๆ
// #include "DHT.h" //ไลบารี่ของเซ็นเซอร์ DHT

// #define DHTTYPE DHT11   // ระบุรุ่นของเซ็นเซอร์ DHT ในที่นี้ใช้เป็น DHT 11
// const int DHTPin = 7; // ระบุขาที่ใช้ต่อกับเซ็นเซอร์ DHT11
// DHT dht(DHTPin, DHTTYPE);

// #define WIFI_SSID "JimJumZz" //กำหนดชื่อเราเตอร์ไวไฟที่ใช้งาน
// #define WIFI_PASSWORD "77777777" //กำหนดพาสเวิร์ดเราเตอร์ไวไฟที่ใช้งาน

// #define API_KEY "AIzaSyAXmqDJETEwU8ecq3wBYtNfH_TYAEQvjqQ" //ค่า Web API Key ที่ได้จากการสร้างบนไฟล์เบส
// #define DATABASE_URL "https://supannikafirebase1-default-rtdb.asia-southeast1.firebasedatabase.app/" //ลิงค์ URL ของดาต้าเบส ได้จากการสร้างบนไฟล์เบส

// //#define LED1_PIN 2 //กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 2
// //#define LED2_PIN 3 //กำหนดใช้งานขาเอาต์พุตแอลอีดีที่ขา 3
// //#define ANA_PIN A0 //กำหนดขาอินพุตที่เป็นแอนาล็อกไว้ที่ขา A0

// FirebaseData fbdo; //สร้างอ็อปเจ็คที่ชื่อว่า fbdo (FireBase Data Output)สำหรับค่าเอาต์พุตดาต้าที่ไมโครเมื่อมีการเปลี่ยนแปลงค่าที่เซ็นเซอร์
// FirebaseAuth auth; //สร้างอ็อปเจ็คที่ชื่อว่า auth (Firebase Authentication) เพื่อใช้สำหรับการยืนยันตัวตนในกรณีที่เข้าใช้งาน Firebase
// FirebaseConfig config; //สร้างอ็อปเจ็คที่ชื่อว่า config เพื่อใช้สำหรับการตั้งค่าต่าง ๆ ระหว่างไมโครคอนโทรเลอร์และไฟล์เบส

// unsigned long sendDataPreMillis = 0; //สร้างตัวแปรชนิด unsigned long เพื่อใช้กับฟังก์ชั่น millis() สำหรับการส่งข้อมูลไปกลับระหว่างไมโครคอนโทรเลอร์และไฟล์เบส
// boolean signupOK = false; //ตัวแปรแบบ bool ใช้เพื่อเก็บค่าการ sing up ของไฟล์เบสว่าสำเร็จหรือไม่ ถ้าสำเร็จให้เก็บค่า 1 ถ้าไม่สำเร็จให้เก็บค่า 0
// //int analogData = 0; //ตัวแปรแบบ int ใช้เก็บข้อมูลขาแอนาล็อกที่ขา A0 โดยมีค่าระหว่าง 0 ถึง 4095
// //float voltage = 0.0; //ตัวแปรแบบ float ใช้เพื่อแปลงค่า analogData ให้เป็นค่าแรงดันไฟฟ้าที่ป้อนเข้ามาที่ขา A0

// void setup() {
//   Serial.begin(115200); //กำหนดอัตราบอร์ดเรตสำหรับติดต่อกับ Serial Monitor อยู่ที่ 115200 บิตต่อวินาที
//   dht.begin(); 
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
    
//     //analogData = analogRead(ANA_PIN); //การอ่านค่าแอนาล็อกจากขา A0 มาเก็บไว้ที่ตัวแปร analogData
//     //voltage = (float)analogReadMilliVolts(ANA_PIN)/1000; //ทำการแปลงค่าจากอินพุตแอนาล็อกที่ขา A0 ให้เป็นค่าแรงดันไฟฟ้าโดยใช้ฟังก์ชั่น analogReadMilliVolts() หน่วยที่ได้เป็นมิลลิโวลต์จึงต้องเอา 1000 ไปหาร แล้วเอามาเก็บไว้ที่ตัวแปร voltage 
//     float h = dht.readHumidity(); // เอาค่าความชื้นมาเก็บไว้ที่ตัวแปร h
//     float t = dht.readTemperature(); //เอาค่าอุณหภูมิมาเก็บไว้ที่ตัวแปร t

//     // การส่งข้อมูลแบบ Float (จุดทศนิยม) ในที่นี้คืออุณหภูมิ (Temperature) ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setFloat(&fbdo, "Sensor/temperature", t)){ //ทำการตรวจสอบค่า analogData ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/ana_data
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(t); //พิมพ์ค่าตัวแปร อุณหภูมิ
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }

//     // การส่งข้อมูลแบบ Int (ตัวเลขจำนวนเต็ม) ในที่นี้คือค่าความชื้น (Humidity) ไปเก็บไว้บนไฟล์เบส
//     if(Firebase.RTDB.setInt(&fbdo, "Sensor/humidity", h)){ //ทำการตรวจสอบค่า voltage ที่บนไฟล์เบสในไดเร็คทอรี่ Sensor/voltage
//       Serial.println(); //ขึ้นบรรทัดใหม่
//       Serial.print(h); //พิมพ์ค่าตัวแปร ความชื้น
//       Serial.print(" - บันทึกข้อมูลบน Firebase สำเร็จ โดยอยู่ในดาต้าพาท: " + fbdo.dataPath()); //แสดงข้อมูลไดเร็คทอรี่บนไฟล์เบส
//       Serial.println("(" + fbdo.dataType() + ")"); //แสดงชนิดของข้อมูลที่ถูกนำไปเก็บบนไฟล์เบส
//     }
//     else{
//       Serial.println("การส่งข้อมูลล้มเหลว: " + fbdo.errorReason()); //กรณีที่ไม่สามารถส่งข้อมูลไปเก็บบนไฟล์เบสได้ให้ขึ้นข้อความที่ถูกตั้งไว้บนไฟล์เบส
//     }
//   }

// }












