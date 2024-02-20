#include <M5Unified.h>
#include <LiquidCrystal_I2C.h>

//I2CアドレスとLCDの画面サイズを指定
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  //M5Unifiedで本体初期化
  auto cfg = M5.config();
  cfg.serial_baudrate = 9600;
  M5.begin(cfg);
  //本体ディスプレイにHello, World!を表示
  M5.Display.setTextSize(3);
  M5.Display.println("Hello, World!");

  //LCD初期化
  lcd.init();
  //呼び出すことでバックライトON 
  lcd.backlight();
  //左上からHello, world!を表示
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
}

void loop(){

}