/**
 * @file syateki_gun_main.ino
 * @brief 射的銃メインプログラム
 */
#include <Arduino.h>
#include "irShooter.hpp"
#include "reactor.hpp"

#define PIN_IN_TRIGGER        14
#define PIN_OUT_IR            13
#define MAGAGINE_CAPACITY     20
#define INITIAL_BULLETS_NUM   MAGAGINE_CAPACITY

IrShooter ir_shooter(PIN_OUT_IR, MAGAGINE_CAPACITY, INITIAL_BULLETS_NUM);

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
  static bool pre_is_trigger_on = false;

  if(digitalRead(PIN_IN_TRIGGER)){
    if(!pre_is_trigger_on){
      //  チャタリング除去対応
      delay(100);
      if(digitalRead(PIN_IN_TRIGGER)){
        ir_shooter.shoot();
        Serial.println("# shoot (remain bullets = " + String(ir_shooter.get_bullets_num()) + ")");
      }
    }
    pre_is_trigger_on = true;
  }else{
    pre_is_trigger_on = false;
  }
}

/**
 * @brief ピン初期化
 * @param None
 * @return None
 */
static void initializePins(){
  pinMode(PIN_IN_TRIGGER, INPUT);
}