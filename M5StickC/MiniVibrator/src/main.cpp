#include <M5Unified.h>

#define OUTPUT_PIN 26

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
    //OUTPUT_PINをHIGHとLOW交互に切り替える
    digitalWrite(OUTPUT_PIN, HIGH);
    delay(100);
    digitalWrite(OUTPUT_PIN, LOW);
    delay(500);
}