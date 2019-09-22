/**
 * @file syateki_gun_main.ino
 * @brief 射的銃メインプログラム
 */
#include <Arduino.h>
#include <WiFi.h>
#include "irShooter.hpp"
#include "reactor.hpp"

#define PIN_IN_TRIGGER        14
#define PIN_OUT_IR            13
#define MAGAGINE_CAPACITY     20
#define INITIAL_BULLETS_NUM   MAGAGINE_CAPACITY
#define DELAY_WAIT_RESET_MS   100
#define TOTAL_RESET_TIME_LIMIT 3000

IrShooter ir_shooter(PIN_OUT_IR, MAGAGINE_CAPACITY, INITIAL_BULLETS_NUM);
Reactor reactor;

/**
 * @brief セットアップ関数
 * @param None
 * @return None
 */
void setup(void) {
  Serial.begin(115200);
  initializePins();
  WiFi.begin("ROBOCON-AP1", "20190216-rc");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {  
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi connect process time out.");
  }
}

/**
 * @brief メインループ関数
 * @param None
 * @return None
 */
void loop(void) {
  static bool pre_is_trigger_on = false;

  if(digitalRead(PIN_IN_TRIGGER) == LOW){
    if(!pre_is_trigger_on){
      //  チャタリング除去対応
      delay(100);
      if(digitalRead(PIN_IN_TRIGGER) == LOW){
        int target_num = shoot();
        //  有効な的に当たった場合
        if(target_num > 0){
          hit();
        }
      }
    }
    //  弾を打ち切った場合
    if(ir_shooter.get_bullets_num() <= 0){
      wait_reset();
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

/**
 * @brief センタサーバルートGET処理
 * @param None
 * @return None
 */
static int get_root(){
  const char* host = "192.168.100.114";
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  WiFiClient client;
  const int Port = 5000;
  if (!client.connect(host, Port)) {
    Serial.println("connection failed");
    return -1;
  }
  String url = "/";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" + 
    "Connection: close\r\n\r\n");
  delay(1000);

  // 返ってきた情報の解析
  bool is_start_body = false;
  String body = "";
  while(client.available()){
    String line = client.readStringUntil('\r');
    line.trim();
    Serial.println(line);
    if(is_start_body){
      body += line;
    }
    if(line == ""){
      is_start_body = true;
    }
  }
  Serial.println();
  Serial.println("body = " + body);
  Serial.println("closing connection");
  if(body == ""){
    return -1;
  }
  return body.toInt();
}

/**
 * @brief 弾発射時に行う一連の処理
 * @param None
 * @return None
 */
static int shoot(){
  //  センターに発射を通知し、的の判定を確認
  int target_num = get_root();
  Serial.println("target_num = " + String(target_num));
  //  弾数管理を更新する
  ir_shooter.shoot();
  Serial.println("# shoot (remain bullets = " + String(ir_shooter.get_bullets_num()) + ")");
  //  発射関係の演出を行う
  reactor.react_to_fire(ir_shooter.get_bullets_num());
  return target_num;
}

/**
 * @brief 得点時に行う一連の処理
 * @param None
 * @return None
 */
static void hit(){
  //  得点間関係の演出を行う
  reactor.react_to_hit();
}

/**
 * @brief リセット待機
 * @param None
 * @return None
 * @note ゲーム開始時、ゲーム終了後等で使う
 */
static void wait_reset(){
  int total_push_time_ms = 0;
  bool is_pre_pushed = false;
  //  トリガを引いていた時間が閾値を超えるまでこのループにとどまり続ける
  while(total_push_time_ms < TOTAL_RESET_TIME_LIMIT){
    if(digitalRead(PIN_IN_TRIGGER) == LOW){
      if(is_pre_pushed){
        total_push_time_ms += DELAY_WAIT_RESET_MS;
      }else{
        is_pre_pushed = true;
      }
    }else{
      is_pre_pushed = false;
    }
    delay(DELAY_WAIT_RESET_MS);
  }
  //  トリガを引いていた時間が閾値を超えたのでリセット
  ir_shooter.reload();
  reactor.reset();
}