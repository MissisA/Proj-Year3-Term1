// ep2.4
//IoT course
//By อาจารย์ธนา อุดมศรีไพบูลย์
/*
Computer Engineering 
University of Phayao

void setup() {
  // put your setup code here, to run once:

}
*/
void loop() {
  // put your main code here, to run repeatedly:

}



// ep2.5

void setup() {
  Serial.begin(9600); //or 115200

}

void loop() {
  Serial.print("Hello World!!");
  //Serial.println("Hello World!!");//เว้นบรรทัด
  Delay(1000); //1 sec
  // Serial.println("Hello World!!");//เว้นบรรทัด
  // Delay(1000); //1 sec
}



//ep2.6
void setup() {
  Serial.begin(9600);
}

void loop() {
  //int a;
  //a = 999;
  int a = 999;
  double b = 89.99;
  char c = 'P';
  Serial.println(a);
  Serial.println("================");
  delay(1000);
  Serial.println(b);
  Serial.println("================");
  delay(1000);
  Serial.println(c);
  Serial.println("================");
  delay(1000);
}



//ep2.7
void setup() {
  Serial.begin(9600);
}

void loop() {
  int a[] = {555, 456, 888, 100};
  double b[] = {99.87, 5.11, 45.00, 11.11};
  char c[] = "IYou";

  Serial.println(a[0]);
  delay(1000);
  Serial.println(a[1]);
  delay(1000);
  Serial.println(a[2]);
  delay(1000);
  Serial.println(a[3]);
  delay(1000);

  // Serial.println(b[0]);
  // delay(1000);
  // Serial.println(b[1]);
  // delay(1000);
  // Serial.println(b[2]);
  // delay(1000);
  // Serial.println(b[3]);
  // delay(1000);

  // Serial.println(c[0]);
  // delay(1000);
  // Serial.println(c[1]);
  // delay(1000);
  // Serial.println(c[2]);
  // delay(1000);
  // Serial.println(c[3]);
  // delay(1000);
}


//ep2.8
void setup() {
  Serial.begin(9600);
}

void loop() {
  int a=10, b=20; //b=24 %หารเอาเศษ
  int c=0;

  c = a+b;
  //c = b-a;
  //c = b*a;
  //c = b/a;
  //c = b%a;

  Serial.println(c);
  delay(1000);
}


//ep2.9
void setup() {
  Serial.begin(9600);
}

void loop() {
  int a=69, b=20;

  Serial.println("Start");

  if (a>b) {
    Serial.println("a มากกว่า b");
    delay(1000);
  }

  Serial.println("Stop");
  
}


//ep2.10
void setup() {
  Serial.begin(9600);
}

void loop() {
  int a=10, b=20;

  Serial.println("Start");

  if (a>b) {
    Serial.println("a มากกว่า b");
    delay(1000);
  }
  else {
    Serial.println("a น้อยกว่า b");
    delay(1000);
  }

  Serial.println("Stop");
  
}


//ep2.11
void setup() {
  Serial.begin(9600);
}

void loop() {
  int a=30, b=20;

  Serial.println("Start");

  if (a>b) {
    Serial.println("a มากกว่า b");
    delay(1000);
  }
  else if (a<=b) {
    Serial.println("a น้อยกว่าหรือเท่ากับ b");
    delay(1000);
  }
  else {
    Serial.println("a เท่ากับ b");
    delay(1000);
  }

  Serial.println("Stop");
  
}


//ep2.12
void setup() {
  Serial.begin(9600);
}

void loop() {
  int i=0;
  for (i=0;i<10;i++) {
    Serial.println("University of Phayao");
    Serial.println(i);
    delay(1000);
  }

}
/*----------------------------------------------------------------*/
void setup() {
  Serial.begin(9600);
}

void loop() {
  int a[] = {555, 456, 888, 100};
  double b[] = {99.87, 5.11, 45.00, 11.11};
  char c[] = "IYou";

  // Serial.println(a[0]);
  // delay(1000);
  // Serial.println(a[1]);
  // delay(1000);
  // Serial.println(a[2]);
  // delay(1000);
  // Serial.println(a[3]);
  // delay(1000);

  for (int i=0;i<4;i++) {
    Serial.println(a[i]);
    delay(1000);
  }

}


//ep2.13
void setup() {
  Serial.begin(9600);
}

void loop() {
  int i=0;
  for (i=0;i<10;i=i+1) { //i เพิ่มขึ้นทีละ 1(0-10) same i++
    Serial.println("University of Phayao");
    Serial.println(i);
    delay(1000);
  }

  for (i=10;i>0;i=i-1) { //i ลดลงทีละ 1(10-1)
    Serial.println("University of Phayao");
    Serial.println(i);
    delay(1000);
  }

}


//ep2.14
void setup() {
  Serial.begin(9600);
}

void loop() {
  int i=0; //นับลง 10
  while (i<10) { //นับลง >, i-1
    Serial.println(i);
    i = i + 1; //นับเพิ่มทีละ 1 (0-9)
    delay(1000);
  }
  Serial.println("Loop Out!!");
}


//ep2.15
void setup() {
  Serial.begin(9600);
}

void loop() {
  cat();
  delay(1000);
}

void cat() {
  Serial.println("===============");
  Serial.println("Animal");
  Serial.println("Home");
  Serial.println("===============");

}


//ep2.16
void setup() {
  Serial.begin(9600);
}

void loop() { //เปลี่ยนค่าตรงนี้
  dog("Cute");
  dog("Black color");
  delay(1000);
}

void dog(String a) { //แสดงผล
  Serial.println(a);
}


//ep2.17
void setup() {
  Serial.begin(9600);
}

void loop() {
  int y = 0;
  y = dog(89); // y=(89+10)=99

  Serial.println(y); //แสดงผล 99
  delay(1000);
}

int dog(int x) {
  x = x + 10; //((x=89)+10) = x=99
  return x; //ส่งกลับไปเก็บใน y
}


//ep2.18
void setup() {
  Serial.begin(9600);
}

void loop() {
  double y = 0;
  y = dog(89.99); // y=(89+10)=99.99

  Serial.println(y); //แสดงผล 99.99
  delay(1000);
}

double dog(double x) {
  x = x + 10; //((x=89)+10) = x=99.99
  return x; //ส่งกลับไปเก็บใน y
}
