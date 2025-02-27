#include <M5Unified.h>

#define OUTPUT_PIN 26

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
    char receivedChar = '\0';  // 受信データを格納する変数（初期値はNULL）

    if (Serial.available() > 0) {
        receivedChar = Serial.read();  // 1文字読み取る
    }

    // 受信データに応じて条件分岐
    if (receivedChar == 'X') {
        digitalWrite(OUTPUT_PIN, LOW);
    } else if (receivedChar == 'O') {
        digitalWrite(OUTPUT_PIN, HIGH);
    }
    delay(50);
}