#include <M5Unified.h>

#define sda_pin 32
int freq       = 10000;
int ledChannel = 0;
int resolution = 10;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(sda_pin, ledChannel);
}

void startMotor() {
    ledcWrite(ledChannel, 255);
}

void stopMotor() {
    ledcWrite(ledChannel, 0);
}

void loop() {
    char receivedChar = '\0';  // 受信データを格納する変数（初期値はNULL）

    if (Serial.available() > 0) {
        receivedChar = Serial.read();  // 1文字読み取る
    }

    // 受信データに応じて条件分岐
    if (receivedChar == 'X') {
        startMotor();
    } else if (receivedChar == 'O') {
        stopMotor();
    }
    delay(50);
}