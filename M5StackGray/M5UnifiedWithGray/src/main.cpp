#include <M5Unified.h>

void setup() {
  auto cfg = M5.config();
  cfg.serial_baudrate = 9600;
  M5.begin(cfg);

  M5.Display.setTextSize(2);
}

void loop() {
  M5.update();
  if(M5.BtnA.wasPressed()){
    M5.Display.println("Button A was pressed");
  }
}
