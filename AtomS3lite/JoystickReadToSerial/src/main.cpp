#include <Arduino.h>
#include <M5AtomS3.h>
#include <FastLED.h>
#include <Wire.h>
#include "M5Unified.h"

#define JOY_ADDR 0x52
#define SCL 1
#define SDA 2


void setup() {
  AtomS3.begin();
  AtomS3.Power.begin();
  Wire.begin(SDA, SCL);
  USBSerial.begin(9600);
  AtomS3.dis.setBrightness(50);
}

char data[100];
void loop(){
  AtomS3.update();

  static uint8_t x_data,y_data,button_data;
  Wire.requestFrom(JOY_ADDR, 3);
  if(Wire.available()){
    x_data = Wire.read();
    y_data = Wire.read();
    button_data = Wire.read();
    sprintf(data, "x:%d y:%d button:%d\n", x_data, y_data, button_data);
    USBSerial.print(data);
  }

  if(AtomS3.BtnA.wasPressed()){
    USBSerial.print("BtnA was pressed");
    AtomS3.dis.drawpix(0x00ff00);
  }
  delay(20);
}
