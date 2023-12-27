#include <M5AtomS3.h>
#include <FastLED.h>
#include "M5Unified.h"
#include <M5GFX.h>

#define motor_pin 2
int freq       = 12000;
int ledChannel = 0;
int resolution = 8;

void Vibrate(float power);

void setup() {
  AtomS3.begin(true);
  AtomS3.dis.setBrightness(100);
  AtomS3.dis.drawpix(0x000000);
  //シリアルポート設定
  Serial.begin(115200); 
  //ピン設定
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(motor_pin,ledChannel);
}

void loop() {
  //ボタンを押したら1秒間振動
  if(AtomS3.BtnA.isPressed()){
    Vibrate(0.5);
    delay(1000);
    Vibrate(0.0);
  }
  delay(50);
  AtomS3.update();
}

//引数の強さ(0-1)の強さで振動
void Vibrate(float power){
  if(power > 1.0) power = 1.0;
  if(power < 0.0) power = 0.0;
  ledcWrite(ledChannel, 255 * power);
}