#include <M5AtomS3.h>
#include <FastLED.h>
#include "M5Unified.h"
#include <M5GFX.h>

void setup() {
    AtomS3.begin(true);  // Init AtomS3Lite.
    AtomS3.dis.setBrightness(100);
}

//ボタンを押すたび、消灯>赤>緑>青を繰り返す
int count = 0;
int color = 0;
void loop() {
    if(AtomS3.BtnA.wasPressed()){
        count = (count+1)%4;
    }
    switch (count % 4)
    {
    case 0:
        color = 0x000000;
        break;
    case 1:
        color = 0xff0000;
        break;
    case 2:
        color = 0x00ff00;
        break;
    case 3:
        color = 0x0000ff;
        break;
    default:
        break;
    }
    AtomS3.dis.drawpix(color);
    AtomS3.update();
    delay(100);
}