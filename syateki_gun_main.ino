/**
 * @file syateki_gun_main.ino
 * @brief 射的銃メインプログラム
 */
#include <Arduino.h>

#define PIN_IN_TRIGGER  14
#define PIN_OUT_IR      13

/**
 * @brief セットアップ関数
 * @param None
 * @return None
 */
void setup(void) {
  Serial.begin(115200);
  initializePins();
}

/**
 * @brief メインループ関数
 * @param None
 * @return None
 */
void loop(void) {
  if(digitalRead(PIN_IN_TRIGGER)){
    digitalWrite(PIN_OUT_IR, HIGH);
    Serial.println("trig on");
  }else{
    digitalWrite(PIN_OUT_IR, LOW);
    Serial.println("trig off");
  }
  delay(1000);
}

/**
 * @brief ピン初期化
 * @param None
 * @return None
 */
static void initializePins(){
  digitalWrite(PIN_OUT_IR, LOW);
  pinMode(PIN_OUT_IR, OUTPUT);
  pinMode(PIN_IN_TRIGGER, INPUT);
}