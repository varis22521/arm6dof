//robot
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <VarSpeedServo.h>
VarSpeedServo sv1;
VarSpeedServo sv2;
VarSpeedServo sv3;
VarSpeedServo sv4;
VarSpeedServo sv5;
VarSpeedServo sv6;
VarSpeedServo sv7;
int vec = A0;
int g = 0;
int axis1 = 90;
int axis2 = 90;
int axis3 = 90;
int axis4 = 90;
int axis5 = 90;
int axis6 = 90;
int axis7 = 90;
#define SCREEN_WIDTH 128 // pixel ความกว้าง
#define SCREEN_HEIGHT 64 // pixel ความสูง 
int val1 = 90, val2 = 90 , val3 = 90, val4 = 90, val5 = 90, val6 = 90;

boolean pas = false;
String mode[4] = {"listen", "aoto", "linear"};
// กำหนดขาต่อ I2C กับจอ OLED
#define OLED_RESET -1 //ขา reset เป็น -1 ถ้าใช้ร่วมกับขา Arduino reset
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int x = 0;
int spd = 35;
int i = 0;
int bt1 = 3, bt2 = 4, bt3 = 5, bt4 = 6;
int led = 13;
int var = 0; // ตัวแปรสำหรับทดสอบแสดงผล
int ic = 2;
const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf1, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfb, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0xef, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc1, 0xf7, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x03, 0xf3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0xf1, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x0f, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x0f, 0xc0, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x0f, 0x80, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x3f, 0xf0, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0xf8, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0xf8, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0xf8, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0xf0, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7c, 0x60, 0x7c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0xe0, 0x7c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0x80, 0x7c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7c, 0x00, 0x7c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x7c, 0x00, 0x7c, 0x30, 0x00, 0x00, 0x0f, 0xf0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x38, 0x00, 0x38, 0x30, 0x00, 0x60, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf2, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x70, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x51, 0xc2, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x59, 0x02, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x49, 0x02, 0x70, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x4c, 0x86, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x7c, 0xcc, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc2, 0x68, 0x30, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x38, 0xe0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {

  sv1.attach(7);
  sv2.attach(8);
  sv3.attach(9);
  sv4.attach(10);
  sv5.attach(11);
  sv6.attach(12);
  pinMode(vec, OUTPUT);
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(bt3, INPUT);
  pinMode(bt4, INPUT);
  Serial.begin(9600);
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
    Serial.println("SSD1306 allocation failed");
  } else {
    Serial.println("ArdinoAll OLED Start Work !!!");
  }
  pinMode(ic, OUTPUT);
  OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  OLED.setTextColor(WHITE, BLACK); //กำหนดข้อความสีขาว ฉากหลังสีดำ
  OLED.setCursor(0, 0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  OLED.setTextSize(2); // กำหนดขนาดตัวอักษร
  OLED.println("RCL"); // แสดงผลข้อความ ALL

  OLED.display(); // สั่งให้จอแสดงผล
  delay(1500);
  OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  OLED.drawBitmap(0, 0,  myBitmap, 128, 64 , WHITE);
  OLED.display();
  delay(2000);
  OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  OLED.display(); // สั่งให้จอแสดงผล
  analogWrite(vec, 0);
  delay(1000);

  analogWrite(vec, 255);
  delay(1000);
  while (pas == false) {
    OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
    OLED.setTextColor(WHITE, BLACK); //กำหนดข้อความสีขาว ฉากหลังสีดำ
    OLED.setCursor(0, 0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
    OLED.setTextSize(2); // กำหนดขนาดตัวอักษร
    OLED.println("Enable"); // แสดงผลข้อความ ALL
    OLED.display(); // สั่งให้จอแสดงผล
    if (digitalRead(bt1) == HIGH) {

      if (digitalRead(bt2) == HIGH) {


        digitalWrite(ic, 0);
        pas = true;
        OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
        OLED.display(); // สั่งให้จอแสดงผล

      }
    }

  }
}
void loop() {


  sv1.write(37, spd); //rotate1 axis1
  sv2.write(105, spd); //updown1 axis2
  sv3.write(102, spd); //forbk   axis3
  sv4.write(90, spd); //rotate2 axis4
  sv5.write(60, spd); //updown2 axis5
  sv6.write(90, spd); //rotate3 axis6

  sv1.wait();
  sv2.wait();
  sv3.wait();
  sv4.wait();
  sv5.wait();
  sv6.wait();
  
  sv1.write(37, spd); //rotate1 axis1
  sv2.write(98, spd); //updown1 axis2
  sv3.write(63, spd); //forbk   axis3
  sv4.write(90, spd); //rotate2 axis4
  sv5.write(80, spd); //updown2 axis5
  sv6.write(90, spd); //rotate3 axis6

  sv1.wait();
  sv2.wait();
  sv3.wait();
  sv4.wait();
  sv5.wait();
  sv6.wait();

  sv1.write(82, spd); //rotate1 axis1
  sv2.write(53, spd); //updown1 axis2
  sv3.write(116, spd); //forbk   axis3
  sv4.write(89, spd); //rotate2 axis4
  sv5.write(56, spd); //updown2 axis5
  sv6.write(90, spd); //rotate3 axis6

  sv1.wait();
  sv2.wait();
  sv3.wait();
  sv4.wait();
  sv5.wait();
  sv6.wait();

  sv1.write(82, spd); //rotate1 axis1
  sv2.write(108, spd); //updown1 axis2
  sv3.write(60, spd); //forbk   axis3
  sv4.write(89, spd); //rotate2 axis4
  sv5.write(92, spd); //updown2 axis5
  sv6.write(90, spd); //rotate3 axis6

  sv1.wait();
  sv2.wait();
  sv3.wait();
  sv4.wait();
  sv5.wait();
  sv6.wait();

  
  sv1.write(82, spd); //rotate1 axis1
  sv2.write(42, spd); //updown1 axis2
  sv3.write(103, spd); //forbk   axis3
  sv4.write(89, spd); //rotate2 axis4
  sv5.write(138, spd); //updown2 axis5
  sv6.write(90, spd); //rotate3 axis6

  sv1.wait();
  sv2.wait();
  sv3.wait();
  sv4.wait();
  sv5.wait();
  sv6.wait();


  
  sv1.write(82, spd); //rotate1 axis1
  sv2.write(93, spd); //updown1 axis2
  sv3.write(156, spd); //forbk   axis3
  sv4.write(93, spd); //rotate2 axis4
  sv5.write(180, spd); //updown2 axis5
  sv6.write(90, spd); //rotate3 axis6

  sv1.wait();
  sv2.wait();
  sv3.wait();
  sv4.wait();
  sv5.wait();
  sv6.wait();
  if (digitalRead(bt1) == HIGH && digitalRead(bt2) == HIGH) {
    analogWrite(vec, 0);
    delay(2000);
    analogWrite(vec, 255);
  }
  if (digitalRead(bt1) == HIGH) {
    delay(100);
    if (digitalRead(bt1) == HIGH) {
      x += 1;
      if (x == 8) {
        x = 0;
      }
    }
  }

  if (x == 8) {
    if (digitalRead(bt2) == HIGH) {
      spd += 1;

    }
    if (digitalRead(bt1) == HIGH) {
      spd -= 1;
    }
  }
  if (x == 1) {


    if (digitalRead(bt3) == HIGH) {
      val1++;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }

    if (digitalRead(bt4) == HIGH) {
      val1--;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }

  }

  if (x == 2) {


    if (digitalRead(bt3) == HIGH) {
      val2++;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }

    if (digitalRead(bt4) == HIGH) {
      val2--;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }
  }
  if (x == 3) {


    if (digitalRead(bt3) == HIGH) {
      val3++;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }

    if (digitalRead(bt4) == HIGH) {
      val3--;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }
  }

  if (x == 4) {


    if (digitalRead(bt3) == HIGH) {
      val4++;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }

    if (digitalRead(bt4) == HIGH) {
      val4--;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }
  }


  if (x == 5) {


    if (digitalRead(bt3) == HIGH) {
      val5++;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }

    if (digitalRead(bt4) == HIGH) {
      val5--;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }
  }
  if (x == 6) {


    if (digitalRead(bt3) == HIGH) {
      val6++;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }

    if (digitalRead(bt4) == HIGH) {
      val6--;
      sv1.write(val1, spd); //rotate1 axis1
      sv2.write(val2, spd); //updown1 axis2
      sv3.write(val3, spd); //forbk   axis3
      sv4.write(val4, spd); //rotate2 axis4
      sv5.write(val5, spd); //updown2 axis5
      sv6.write(val6, spd); //rotate3 axis6

      sv1.wait();
      sv2.wait();
      sv3.wait();
      sv4.wait();
      sv5.wait();
      sv6.wait();

    }
  }

  Serial.print("spd");
  Serial.print(" ");
  Serial.print(spd);
  Serial.print(" ");
  Serial.print("SERVO");
  Serial.print(" ");
  Serial.print(x);
  Serial.print(" ");
  Serial.print("sv1");
  Serial.print(" ");
  Serial.print(val1);
  Serial.print(" ");
  Serial.print("sv2");
  Serial.print(" ");
  Serial.print(val2);
  Serial.print(" ");
  Serial.print("sv3");
  Serial.print(" ");
  Serial.print(val3);
  Serial.print(" ");
  Serial.print("sv4");
  Serial.print(" ");
  Serial.print(val4);
  Serial.print(" ");
  Serial.print("sv5");
  Serial.print(" ");
  Serial.print(val5);
  Serial.print(" ");
  Serial.print("sv6");
  Serial.print(" ");
  Serial.println(val6);
  OLED.clearDisplay();
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(40, 0);
  OLED.setTextSize(2);
  OLED.println("INFO");
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(0, 0);
  OLED.setTextSize(1);
  OLED.println(val1);
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(0, 10);
  OLED.setTextSize(1);
  OLED.println(val2);
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(0, 20);
  OLED.setTextSize(1);
  OLED.println(val3);
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(0, 30);
  OLED.setTextSize(1);
  OLED.println(val4);

  OLED.setTextColor(WHITE, BLACK); //กำหนดข้อความสีขาว ฉากหลังสีดำ
  OLED.setCursor(0, 40); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  OLED.setTextSize(1); // กำหนดขนาดตัวอักษร
  OLED.println(val5); // แสดงผลข้อความ ALL

  OLED.setTextColor(WHITE, BLACK); //กำหนดข้อความสีขาว ฉากหลังสีดำ
  OLED.setCursor(0, 50); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  OLED.setTextSize(1); // กำหนดขนาดตัวอักษร
  OLED.println(val6); // แสดงผลข้อความ ALL
  OLED.display(); // สั่งให้จอแสดงผล




}
