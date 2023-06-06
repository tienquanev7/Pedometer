#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu;
float vector,totalvector,vectorprevious,a,b,c;
int Steps = -1;
int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Gioi thieu");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 17);
  display.println("San pham");
  display.println("Pedometer");

  display.display();

  delay(1000);
}

void loop() {

  while (1){
    display.clearDisplay();
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    data.X = map(ax, -17000, 17000, 0, 255);  // X axis data
    data.Y = map(ay, -17000, 17000, 0, 255);
    data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
    delay(500);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("So buoc");
    display.println("chan: ");
    a= (float(data.X));
    b= (float(data.Y));
    c= (float(data.Z));
    vector = sqrt( (a * a ) + (b *b) + (c * c) );
    totalvector = vector - vectorprevious;
    vectorprevious = vector;
    if ((totalvector>6) || (totalvector<-6)){
      Steps++;
    }
    display.setCursor(0, 34);
    display.print(Steps);
    display.display();
    delay(1000);
  }

  display.display();
  delay(5000);
}