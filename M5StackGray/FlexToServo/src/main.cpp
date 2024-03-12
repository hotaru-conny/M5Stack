#include <M5Unified.h>

int servoPin = 16;
//flexセンサは3.3V電源を使用し、10kΩ抵抗とつないで使用した
int flexPin = 2;

//PWMの設定
const double PWM_Hz = 50;   //PWM周波数
const uint8_t PWM_level = 16; //PWM 16bit(0～65535)

void setup() {
  //M5Stackの初期化
  auto cfg = M5.config();
  cfg.serial_baudrate = 9600;
  M5.begin(cfg);

  //ディスプレイの設定
  M5.Display.setTextSize(3);
  M5.Display.println("Hello, World!");

  //フレックスセンサのピンの設定
  pinMode(flexPin, INPUT);

  //モータのPWMのチャンネル、周波数の設定
  pinMode(servoPin, OUTPUT);
  ledcSetup((uint8_t)1, PWM_Hz, PWM_level);
  //モータのピンとチャンネルの設定
  ledcAttachPin(servoPin, 1);
}
void loop() {
  M5.update();

  //flexセンサの値を取得
  int flexValue = analogRead(flexPin);
  M5.Display.setCursor(0, 0);
  M5.Display.printf("flexValue: %d\n", flexValue);

  //サーボの角度を変更
  //サンプルプログラムで2300-9000の範囲を使用していたので、その範囲にマッピング
  int servoValue = map(flexValue, 2600, 3300, 2300, 9000);
  ledcWrite(1, servoValue);
  //サーボ
  // for (int i = 2300; i <= 9000; i=i+100) {
  //   ledcWrite(1, i);
  //   delay(30);
  //   Serial.printf("%d\n", i);
  // }
  // for (int i = 9000; i > 2300; i=i-100) {
  //   ledcWrite(1, i);
  //   delay(30);
  //   Serial.printf("%d\n", i);
  // }
}