// #define Int_wheel_R 2 //กำหนดขาอินพุตที่ต่อจากเซ็นเซอร์ Opto ที่ล้อขวา (ที่ขา INT 0)
// #define Int_wheel_L 3 //กำหนดขาอินพุตที่ต่อจากเซ็นเซอร์ Opto ที่ล้อซ้าย (ที่ขา INT 1)
// #define PI 3.1415926535897932384626433832795 //กำหนดค่าของ Pi
// #define Wheel_Radiant 3.4925 // รัศมีของล้อ
// //ล้อขวา
// int ENA=10; //กำหนดให้ขาที่ 10 เชื่อมต่อกับขา ENA ของ L298N
// int IN1=9; //กำหนดให้ขาที่ 9 เชื่อมต่อกับขา IN1 ของ L298N
// int IN2=8; //กำหนดให้ขาที่ 8 เชื่อมต่อกับขา IN2 ของ L298N
// //ล้อซ้าย
// int ENB=5; //กำหนดให้ขาที่ 5 เชื่อมต่อกับขา ENB ของ L298N
// int IN3=7; //กำหนดให้ขาที่ 7 เชื่อมต่อกับขา IN3 ของ L298N
// int IN4=6; //กำหนดให้ขาที่ 6 เชื่อมต่อกับขา IN4 ของ L298N

// volatile unsigned int noClk_R = 0; //กำหนดตัวแปรที่ใช้นับจำนวน 1 พัลส์จาก Encoder Disk ที่ล้อขวา
// volatile unsigned int noClk_L = 0; //กำหนดตัวแปรที่ใช้นับจำนวน 1 พัลส์จาก Encoder Disk ที่ล้อซ้าย

// float noSlots = 20.00; //จำนวนช่องว่างของ Encoder Disk บนจานล้อหมุน
// float round_distance = 2*PI*Wheel_Radiant; //ระยะทางของล้อหุ่นยนต์ต่อการหมุน 1 รอบ (เส้นรอบวง) หน่วยเป็น ซม. ใช้สูตร 2xPixรัศมีของล้อ
// float one_tick = round_distance/noSlots; //ค่าระยะทางการเดินทางของล้อจำนวน 1 พัลส์ที่นับได้จากขา IRQ
// float length_wheelbase = 13.5; //ค่าความยาวของฐานล้อ หน่วยเป็นเซ็นติเมตร
// float circumference = 2*PI*length_wheelbase; //ระยะทางการเคลื่อนที่ของหุ่นยนต์ในล้อซ้ายหรือล้อขวาในกรณีหมุนครบ 360 องศา Question 1
// float TT_noPulse_IRQ = circumference/one_tick; //จำนวนพัลส์ที่นับได้ใน ISR ที่ล้อซ้ายหรือล้อขวาในกรณีที่หุ่นยนต์เลี้ยวครบ 360 องศา Question 2
// float anglePerIRQ = 360/TT_noPulse_IRQ; //ค่าองศาที่เกิดขึ้นของการเลี้ยวต่อการนับจำนวนพัลส์ 1 พัลส์ใน ISR Question 3

// float distance_R = 0; //ตัวแปรที่ใช้เก็บระยะทางการเดินทางของล้อขวาหน่วยเป็นเซ็นติเมตร
// float distance_L = 0; //ตัวแปรที่ใช้เก็บระยะทางการเดินทางของล้อซ้ายหน่วยเป็นเซ็นติเมตร

// void ISR_count_R(){ // นับจำนวนพัลส์ที่ผ่านช่องว่างของ Encoder Disk บนจานล้อหมุนที่ล้อขวา
//   noClk_R = noClk_R + 1; //เพิ่มค่าจำนวนของตัวแปรที่ใช้นับ IRQ ที่ล้อขวาไป 1
// }

// void ISR_count_L(){ // นับจำนวนพัลส์ที่ผ่านช่องว่างของ Encoder Disk บนจานล้อหมุนที่ล้อซ้าย
//   noClk_L = noClk_L + 1; //เพิ่มค่าจำนวนของตัวแปรที่ใช้นับ IRQ ที่ล้อซ้ายไป 1
// }
// //ฟังก์ชั่นนี้จะทำการแปลงระยะทางการเดินของหุ่นยนต์จากหน่วยเซ็นติเมตรเป็นจำนวนพัลส์ที่ต้องนับใน ISR สำหรับดักค่า IRQ ในล้อซ้ายและล้อขวา ใช้ในกรณีเดินหน้าและถอยหลัง
// int CM_To_noClk(float IP_cm){
//   float TT_noClk_B = IP_cm/one_tick;
//   int TT_noClk = (int) TT_noClk_B;
//   return TT_noClk;
// }
// //ฟังก์ชั่นนี้จะทำการแปลงความเร็วของหุ่นยนต์จากหน่วยเซ็นติเมตร/วินาทีเป็นค่า Duty Cycle ของ PWM เพื่อใช้ป้อนให้กับขา ENA และ ENB ของ L298N
// int SP_To_PWM(float IP_sp){
//   int TT_PWM = map(IP_sp,0,70,0,4095); //แม็พค่าความเร็วสูงสุดของหุ่นยนต์ ในที่นี้คือ 70 เซ็นติเมตรต่อวินาทีให้มีค่าระหว่าง 0-4095
//   return TT_PWM;
// }
// //ฟังก์ชั่นนี้จะทำการแปลงค่าองศาการเลี้ยวของหุ่นยนต์ไปเป็นจำนวนพัลส์ที่ต้องนับใน ISR สำหรับดักค่า IRQ ในล้อซ้ายหรือล้อขวา ใช้ในกรณีเลี้ยวซ้ายและเลี้ยวขวา
// int DGT_To_noClk(float IP_dg){
//   float TT_noClk_D = IP_dg*(1/anglePerIRQ);
//   int TT_noClk = (int) TT_noClk_D;
//   return TT_noClk;
// }
// //ฟังก์ชั่นนี้จะทำการแปลงค่าองศาการหมุนของหุ่นยนต์ไปเป็นจำนวนพัลส์ที่ต้องนับใน ISR สำหรับดักค่า IRQ ในล้อซ้ายและล้อขวา ใช้ในกรณีหมุนซ้ายและหมุนขวา
// int DGR_To_noClk(float IP_dgr){
//   float TT_noClk_DR = IP_dgr*(1/(2*anglePerIRQ));
//   int TT_noClk = (int) TT_noClk_DR;
//   return TT_noClk;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่ อินพุตจะมี 2 ค่าคือ ความเร็วของหุ่นยนต์มีหน่วยเป็นเซ็นติเมตรต่อวินาที และ ระยะทางที่ต้องการให้หุ่นยนต์เคลื่อนที่มีหน่วยเป็นเซ็นติเมตร
// void forward(float CMpS_speed, float CM_distance){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เดินไปด้านหน้า
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าระยะทางที่ต้องการให้หุ่นยนต์เคลื่อนที่เป็นจำนวนพัลส์ที่ต้องใช้นับใน ISR
//   int Pulse_distance = CM_To_noClk(CM_distance);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_distance > noClk_R && Pulse_distance > noClk_L){
//     //ในกรณีล้อขวา
//     if(Pulse_distance > noClk_R){ 
//       analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
//     }
//     else{
//       analogWrite(ENA, 0); //ถ้าถึงระยะทางที่กำหนดให้ล้อขวาหยุด
//     }
//     //ในกรณีล้อซ้าย
//     if(Pulse_distance > noClk_L){
//       analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
//     }
//     else{
//       analogWrite(ENB, 0); //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายหยุด
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์เคลื่อนที่ไปด้านหลังด้วยความเร็วคงที่ อินพุตจะมี 2 ค่าคือ ความเร็วของหุ่นยนต์มีหน่วยเป็นเซ็นติเมตรต่อวินาที และ ระยะทางที่ต้องการให้หุ่นยนต์เคลื่อนที่มีหน่วยเป็นเซ็นติเมตร
// void backward(float CMpS_speed, float CM_distance){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เดินถอยหลัง
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าระยะทางที่ต้องการให้หุ่นยนต์เคลื่อนที่เป็นจำนวนพัลส์ที่ต้องใช้นับใน ISR
//   int Pulse_distance = CM_To_noClk(CM_distance);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_distance > noClk_R && Pulse_distance > noClk_L){
//     //ในกรณีล้อขวา
//     if(Pulse_distance > noClk_R){ 
//       analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
//     }
//     else{
//       analogWrite(ENA, 0); //ถ้าถึงระยะทางที่กำหนดให้ล้อขวาหยุด
//     }
//     //ในกรณีล้อซ้าย.............
//     if(Pulse_distance > noClk_L){
//       analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
//     }
//     else{
//       analogWrite(ENB, 0); //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายหยุด
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการเลี้ยวขวาแบบเดินหน้า อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการเลี้ยวมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการเลี้ยวมีหน่วยเป็นองศา
// void turn_right_forward(float CMpS_speed, float DG_turn){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการเลี้ยวขวา (ใช้เหมือนกับกรณีเดินหน้าเพียงแต่ว่ากำหนดความเร็วให้เพียงล้อซ้ายและหยุดล้อขวา)
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าองศาการเลี้ยวให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อซ้าย
//   int Pulse_angle = DGT_To_noClk(DG_turn);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อซ้ายว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_angle > noClk_L){
//     //ในกรณีล้อซ้าย
//     if(Pulse_angle > noClk_L){
//       analogWrite(ENA, 0); //ล้อขวาหยุดหมุน
//       analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
//     }
//     else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
//       analogWrite(ENA, 0);
//       analogWrite(ENB, 0); 
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการเลี้ยวขวาแบบถอยหลัง อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการเลี้ยวมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการเลี้ยวมีหน่วยเป็นองศา
// void turn_right_backward(float CMpS_speed, float DG_turn){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการเลี้ยวขวา (ใช้เหมือนกับกรณีเดินหน้าเพียงแต่ว่ากำหนดความเร็วให้เพียงล้อซ้ายและหยุดล้อขวา)
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าองศาการเลี้ยวให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อซ้าย
//   int Pulse_angle = DGT_To_noClk(DG_turn);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อซ้ายว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_angle > noClk_L){
//     //ในกรณีล้อซ้าย
//     if(Pulse_angle > noClk_L){
//       analogWrite(ENA, 0); //ล้อขวาหยุดหมุน
//       analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
//     }
//     else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
//       analogWrite(ENA, 0);
//       analogWrite(ENB, 0); 
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการเลี้ยวซ้ายแบบเดินหน้า อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการเลี้ยวมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการเลี้ยวมีหน่วยเป็นองศา
// void turn_left_forward(float CMpS_speed, float DG_turn){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการเลี้ยวซ้าย (ใช้เหมือนกับกรณีเดินหน้าเพียงแต่ว่ากำหนดความเร็วให้เพียงล้อขวาและหยุดล้อซ้าย)
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าองศาการเลี้ยวให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อขวา
//   int Pulse_angle = DGT_To_noClk(DG_turn);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อขวาว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_angle > noClk_R){
//     //ในกรณีล้อขวา
//     if(Pulse_angle > noClk_R){
//       analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
//       analogWrite(ENB, 0); //ล้อซ้ายหยุดหมุน
//     }
//     else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
//       analogWrite(ENA, 0);
//       analogWrite(ENB, 0); 
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการเลี้ยวซ้ายแบบถอยหลัง อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการเลี้ยวมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการเลี้ยวมีหน่วยเป็นองศา
// void turn_left_backward(float CMpS_speed, float DG_turn){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการเลี้ยวซ้าย (ใช้เหมือนกับกรณีเดินหน้าเพียงแต่ว่ากำหนดความเร็วให้เพียงล้อขวาและหยุดล้อซ้าย)
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าองศาการเลี้ยวให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อขวา
//   int Pulse_angle = DGT_To_noClk(DG_turn);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อขวาว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_angle > noClk_R){
//     //ในกรณีล้อขวา
//     if(Pulse_angle > noClk_R){
//       analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
//       analogWrite(ENB, 0); //ล้อซ้าย
//     }
//     else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
//       analogWrite(ENA, 0);
//       analogWrite(ENB, 0); 
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการหมุนขวา อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการหมุนมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการหมุนมีหน่วยเป็นองศา
// void spin_right(float CMpS_speed, float DG_spin){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการหมุนขวา (ล้อซ้ายเดินหน้าล้อขวาถอยหลัง)
//   digitalWrite(IN1, HIGH); //ล้อซ้าย
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW); //ล้อขวา
//   digitalWrite(IN4, HIGH);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าองศาการหมุนให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อขวา
//   int Pulse_angle = DGR_To_noClk(DG_spin);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อซ้ายว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_angle > noClk_L){
//     //ในกรณีล้อซ้ายและขวา
//     if(Pulse_angle > noClk_L){
//       analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
//       analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
//     }
//     else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
//       analogWrite(ENA, 0);
//       analogWrite(ENB, 0); 
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์ทำการหมุนซ้าย อินพุตมีอยู่ 2 ค่าคือ ค่าความเร็วของการหมุนมีหน่วยเป็นเซ็นติเมตรต่อวินาทีและองศาการหมุนมีหน่วยเป็นองศา
// void spin_left(float CMpS_speed, float DG_spin){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์ทำการหมุนซ้าย (ล้อซ้ายถอยหลังล้อขวาเดินหน้า)
//   digitalWrite(IN1, LOW); //ล้อซ้าย
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, HIGH); //ล้อขวา
//   digitalWrite(IN4, LOW);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
//   //ทำการแปลงค่าความเร็วของหุ่นยนต์เป็น PWM
//   int PWM_speed = SP_To_PWM(CMpS_speed);
//   //ทำการแปลงค่าองศาการหมุนให้เป็นค่าจำนวนพัลส์ที่จะต้องใช้นับในล้อขวา
//   int Pulse_angle = DGR_To_noClk(DG_spin);
//   //ทำการดักค่าจำนวนพัลส์ใน IRQ ที่ล้อขวาว่าครบตามกำหนดระยะทางแล้วหรือยังถ้าครบตามจำนวนที่กำหนดแล้วให้หุ่นยนต์หยุดการเคลื่อนที่
//   while (Pulse_angle > noClk_R){
//     //ในกรณีล้อซ้ายและขวา
//     if(Pulse_angle > noClk_R){
//       analogWrite(ENA, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อขวา
//       analogWrite(ENB, PWM_speed); //ถ้ายังไม่ถึงระยะทางที่กำหนดให้ใส่ PWM ไปที่ล้อซ้าย
//     }
//     else{ //ถ้าถึงระยะทางที่กำหนดให้ล้อซ้ายและขวาหยุด
//       analogWrite(ENA, 0);
//       analogWrite(ENB, 0); 
//     }
//   }
//   //ใช้สำหรับดักค่า PWM ในกรณีที่ Duty Cycle ต่ำกว่าที่ L298N จะสามารถเอาไปขับมอเตอร์ให้หมุนได้ ป้องกันความเสียหายของมอเตอร์ในช่วง 0-2050 (ในที่นี้ความเร็วในการสั่งงานของมอเตอร์อยู่ที่ 0 - 4095)
//   if (PWM_speed < 2050){
//     PWM_speed = 0;
//   }
//   //ทำการหยุดการเคลื่อนที่ของหุ่นยนต์เมื่อทำภารกิจเดินหน้าสำเร็จตามระยะทางที่กำหนด
//   analogWrite(ENA, 0);
//   analogWrite(ENB, 0);
//   //ทำการล้างค่าการนับใน IRQ ทั้งล้อซ้ายและล้อขวา
//   noClk_R = 0;
//   noClk_L = 0;
// }

// //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์หยุดเดิน
// void stop(){
//   //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่นยนต์เพื่อให้หุ่นยนต์หยุดเดิน
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
// }

// void setup() {
//   pinMode(ENA, OUTPUT);
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(ENB, OUTPUT);
//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);
//   //กำหนดค่าในการทำ Hardware IRQ
//   attachInterrupt(digitalPinToInterrupt(Int_wheel_R), ISR_count_R, RISING); // กำหนดพารามิเตอร์สำหรับ HW IRQ ให้กับล้อขวาเพื่อนับจำนวนพัลส์ที่ขอบขาขึ้น
//   attachInterrupt(digitalPinToInterrupt(Int_wheel_L), ISR_count_L, RISING); // กำหนดพารามิเตอร์สำหรับ HW IRQ ให้กับล้อซ้ายเพื่อนับจำนวนพัลส์ที่ขอบขาขึ้น
//   //เปลี่ยนความละเอียดของ PWM จาก 0 - 255 เป็น 0 - 4095
//   analogWriteResolution(12);
// }

// void loop() {
//   //ความเร็วสูงสุดของหุ่นยนต์ที่ทำได้คือ 70 ซม/วินาที
//   forward(60, 400); //เคลื่อนที่ไปข้างหน้าด้วยความเร็ว 60 ซม/วินาที เป็นระยะทาง 100 ซม
//   delay(3000);
//   // backward(50, 70); //เคลื่อนที่ถอยหลังด้วยความเร็ว 50 ซม/วินาที เป็นระยะทาง 70 ซม
//   // delay(3000);

//   // turn_right_forward(65, 180); //ทำการเลี้ยวขวา (ไปข้างหน้า) ด้วยความเร็ว 65 ซม/วินาที โดยทำการเลี้ยว 180 องศา
//   // delay(3000);
//   // // turn_right_backward(55, 90); //ทำการเลี้ยวขวา (ถอยหลัง) ด้วยความเร็ว 55 ซม/วินาที โดยทำการถอยเลี้ยว 90 องศา
//   // delay(3000);
//   // turn_left_forward(70, 180); //ทำการเลี้ยวซ้าย (ไปข้างหน้า) ด้วยความเร็ว 70 ซม/วินาที (สูงสุด) โดยทำการเลี้ยว 180 องศา
//   // delay(3000);
//   // turn_left_backward(60, 270); //ทำการเลี้ยวซ้าย (ถอยหลัง) ด้วยความเร็ว 60 ซม/วินาที (สูงสุด) โดยทำการเลี้ยว 270 องศา
//   // delay(3000);
//   // spin_right(65, 360); //ทำการหมุนขวาด้วยความเร็ว 65 ซม/วินาที ด้วยองศาการหมุน 360 องศา
//   // delay(3000);
//   // spin_left(60, 180); //ทำการหมุนซ้ายด้วยความเร็ว 60 ซม/วินาที ด้วยองศาการหมุน 180 องศา
//   // delay(3000);
//   // stop();
//   // delay(500);
// }








int ENA=10;
int IN1=9;
int IN2=8;
//มอเตอร์ขวา
int ENB=5;
int IN3=7;
int IN4=6;
//ตัวแปรรับค่า PWM จากไมโครฯ เพื่อควบคุมความเร็วทั้งล้อซ้ายและขวา
int MotorSpeed_L = 4000;
int MotorSpeed_R = 4000;
//ตัวแปรสำหรับลดความเร็วของล้อในการทำ PID
int B_L = 0;
int B_R = 1500;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //การเพิ่มความละเอียดของ PWM เพื่อใช้ปรับความเร็วของมอเตอร์
  analogWriteResolution(12); //มีค่าตั้งแต่ 0 - 4095
}

void forward(){
  //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //กำหนดความเร็วให้กับมอเตอร์ 
  
  if(MotorSpeed_L < 1800){
    MotorSpeed_L = 0;
  }
  if(MotorSpeed_R < 1800){
    MotorSpeed_R = 0;
  }
  analogWrite(ENA, MotorSpeed_L - B_L); //มอเตอร์ซ้าย
  analogWrite(ENB, MotorSpeed_R - B_R); //มอเตอร์ขวา
}

void backward(){
  //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์เคลื่อนที่ไปด้านหน้าด้วยความเร็วคงที่
  //กำหนดพารามิเตอร์ที่ L298N เพื่อให้หุ่่นยนต์เดินไปด้านหน้า
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  //กำหนดความเร็วให้กับมอเตอร์ 
  
  if(MotorSpeed_L < 1800){
    MotorSpeed_L = 0;
  }
  if(MotorSpeed_R < 1800){
    MotorSpeed_R = 0;
  }
  analogWrite(ENA, MotorSpeed_L - B_L); //มอเตอร์ซ้าย
  analogWrite(ENB, MotorSpeed_R - B_R); //มอเตอร์ขวา
}
 
void forward_left(){
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวซ้าย
  //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายหยุดและขวาที่ค่าความเร็ว 4000
  analogWrite(ENA, MotorSpeed_L - B_L);
  analogWrite(ENB, 0);
}
 
void backward_left(){
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวซ้ายแบบถอยหลัง
  //กำหนดให้พารามิเตอร์ที่ L298N ให้ถอยหลัง
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายหยุดและขวาที่ค่าความเร็ว 4000
  analogWrite(ENA, 0);
  analogWrite(ENB, MotorSpeed_R - B_R);
}
 
void forward_right(){
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์เลี้ยวขวา
  //กำหนดให้พารามิเตอร์ที่ L298N เดินหน้า
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายที่ค่าความเร็ว 4000 และขวาหยุด
  analogWrite(ENB, 0);
  analogWrite(ENB, MotorSpeed_R - B_R);
  
}
 
void backward_right(){
  // ฟังก์ชั่นนี้จะให้หุ่นยนต์ถอยหลังเลี้ยวขวา
  //กำหนดให้พารามิเตอร์ที่ L298N ให้ถอยหลัง
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายที่ค่าความเร็ว 4000 และขวาหยุด
  analogWrite(ENA, 0);
  analogWrite(ENB, MotorSpeed_R - B_R);
}
 
void around_right(){
  //ฟังก์ชั่นนี้จะให้หุ่นยนต์หมุนรอบตัวเองไปทางขวา
  //กำหนดให้พารามิเตอร์ที่ L298N หมุนขวา
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // ใส่ความเร็วให้กับมอเตอร์ซ้ายและขวาที่ค่าความเร็ว 4000
  analogWrite(ENA, 4000-B_L);
  analogWrite(ENB, 4000-B_R);
}
 
void around_left(){
  //ฟังก์ชั่นนี้จะให้หุ่นยนต์หมุนรอบตัวเองไปทางซ้าย
  //กำหนดให้พารามิเตอร์ที่ L298N หมุนซ้าย
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  //กำหนดความเร็วให้กับมอเตอร์ 
  if(MotorSpeed_L < 1800){
    MotorSpeed_L = 0;
  }
  if(MotorSpeed_R < 1800){
    MotorSpeed_R = 0;
  }
  analogWrite(ENA, MotorSpeed_L - B_L); //มอเตอร์ซ้าย
  analogWrite(ENB, MotorSpeed_R - B_R); //มอเตอร์ขวา
}
 
void stop(){
  //ฟังก์ชั่นนี้จะทำให้หุ่นยนต์หยุดเดิน คือการสั่งให้มอเตอร์ซ้ายและขวาหยุด
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void loop() {
  int t = 1000;
  int turnT = t*4.9;

  // //ตรงสั้น
  // forward();
  // delay(t*10);
  // stop();
  // delay(t*1);

  // forward_right();
  // delay(t*0.3);
  // stop();
  // delay(t*1);


  //ตรงยาว
  forward();
  delay(t*7);
  stop();
  delay(t*1);


  forward_left();
  delay(t*0.40);
  stop();
  delay(t*1);

  forward();
  delay(t*5);
  stop();
  delay(t*1);

  forward_left();
  delay(t*0.40);
  stop();
  delay(t*1);


  forward();
  delay(t*3);
  stop();
  delay(t*1);



  forward_right();
  delay(t*8);
  stop();
  delay(t*1);


//

forward();
  delay(t*7);
  stop();
  delay(t*1);


  forward_left();
  delay(t*0.40);
  stop();
  delay(t*1);

  forward();
  delay(t*5);
  stop();
  delay(t*1);

  forward_left();
  delay(t*0.44);
  stop();
  delay(t*1);


  forward();
  delay(t*6);
  stop();
  delay(t*1);



  forward_right();
  delay(t*8);
  stop();
  delay(t*1);

  







  

  // //ตรงยาว
  // forward();
  // delay(t*7);
  // // stop();
  // // delay(t*1);

  // forward_right();
  // delay(t*0.34);
  // // stop();
  // // delay(t*1);

  // forward();
  // delay(t*9.8);
  // stop();
  // delay(t*1);

  // //เลี้ยว
  // backward_right();
  // delay(turnT);
  // // stop();
  // // delay(t*1);

  // backward_right();
  // delay(t*0.49);
  // // stop();
  // // delay(t*1);

  // forward_right();
  // delay(t*0.3);
  // stop();
  // delay(t*1);
  
  // // //ตรงสั้น
  // // forward();
  // // delay(t*5);
  // // // stop();
  // // // delay(t*1);

  // // backward_right();
  // // delay(t*0.22);
  // // // stop();
  // // // delay(t*1);

  // // forward();
  // // delay(t*5);
  // // // stop();
  // // // delay(t*1);

  // // forward_right();
  // // delay(t*0.34);
  // // // stop();
  // // // delay(t*1);

  // // forward();
  // // delay(t*4);
  // // // stop();
  // // // delay(t*1);

  //  //เลี้ยว
  // backward_right();
  // delay(turnT);
  // // stop();
  // // delay(t*1);

  // backward_right();
  // delay(t*0.35);
  // // stop();
  // // delay(t*1);

  // //ตรงยาว
  // forward();
  // delay(t*5);
  // // stop();
  // // delay(t*1);

  // forward_right();
  // delay(t*0.32);
  // // stop();
  // // delay(t*1);

  // forward();
  // delay(t*9.3);
  // stop();
  // delay(t*5);
}