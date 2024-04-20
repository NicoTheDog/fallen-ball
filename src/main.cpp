#include "M5Stack.h"

#define POS_X_MIN 0
#define POS_X_MAX 360
#define POS_Y_MIN 0
#define POS_Y_MIN 240


TFT_eSprite sprite = TFT_eSprite(&M5.Lcd);

float t = 0.0f; // 画面の上端座標
float b = 160.0f; // 画面の下端座標
float g = 9.8f; // 重力加速度
float m = 1.0f; // ボールの質量
float r = 10.0f; // ボールの半径
float k = 20.0f; // バネ定数
float c = 2.0f; // 粘性係数
float x = t+r; // ボールの位置（中心座標）
float v = 0.0f; // ボールの速度

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;
float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

void setup() {
  M5.begin();
  M5.IMU.Init();

  sprite.createSprite(M5.Lcd.width(),M5.Lcd.height());
}

void loop() {
  M5.update();
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  if(M5.BtnA.wasPressed()) {
    x = r;
    v = 0.0;
  }
  float f = m * g;
  if(x+r > b) {
    float f2 = k * ((x+r)-b);
    float f3 = c * v;
    f = f - f2 - f3;
  }
  float a = f / m / 10;
  v += a;
  x += v;

  sprite.fillScreen(BLACK);
  // M5.Lcd.fillScreen(BLACK);
  sprite.fillCircle((int)x, 40, (int)r, YELLOW);
  sprite.fillCircle((int)x+60, 40, (int)r, GREEN);
  
  sprite.setCursor(10, 10, 1); 
  sprite.printf("gyroX = %6.2f gyroY = %6.2f gyroZ = %6.2f accX = %5.2f accY = %5.2f accZ = %5.2f",gyroX,gyroY,gyroZ,accX,accY,accZ);
  // M5.Lcd.fillCircle((int)x, 40, (int)r, YELLOW);
  sprite.pushSprite(0, 0);
}