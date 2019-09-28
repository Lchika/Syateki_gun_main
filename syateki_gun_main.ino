/**
 * @file syateki_gun_main.ino
 * @brief 射的銃メインプログラム
 */
#include <Arduino.h>
#include <WiFi.h>
#include "debug.h"
#include "irShooter.hpp"
#include "reactor.hpp"

//  内部関数宣言
void setup(void);
void loop(void);
static void initializePins(void);
static int get_root(void);
static int shoot(void);
static void hit(void);
static void wait_until(int total_time_ms, int ref_pin, int delay_wait_ms, uint8_t ref_level = LOW);
static void reset_game(void);

//  定数宣言
static int constexpr PIN_IN_TRIGGER = 14;     //  トリガ入力ピン
static int constexpr PIN_OUT_IR     = 13;     //  赤外線出力用ピン
static unsigned int constexpr MAGAGINE_CAPACITY   = 20;                 //  マガジン最大装填量
static unsigned int constexpr INITIAL_BULLETS_NUM = MAGAGINE_CAPACITY;  //  初期弾数
static int constexpr DELAY_WAIT_RESET_MS    = 100;    //  リセット待機用delay時間[ms]
static int constexpr TOTAL_RESET_TIME_LIMIT = 3000;   //  リセット待機用合計時間[ms]

//  変数宣言
IrShooter ir_shooter(PIN_OUT_IR, MAGAGINE_CAPACITY, INITIAL_BULLETS_NUM);
Reactor reactor;

//  関数定義
/**
 * @brief セットアップ関数
 * @param None
 * @return None
 */
void setup(void) {
  BeginDebugPrint();
  initializePins();
  WiFi.begin("ROBOCON-AP1", "20190216-rc");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    DebugPrint(".");
  }
  if (WiFi.status() == WL_CONNECTED) {  
    DebugPrint("");
    DebugPrint("WiFi connected.");
    DebugPrint("IP address: ");
    DebugPrint(WiFi.localIP().toString().c_str());
  } else {
    DebugPrint("WiFi connect process time out.");
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
      wait_by_pinlevel(TOTAL_RESET_TIME_LIMIT, PIN_IN_TRIGGER, DELAY_WAIT_RESET_MS, LOW);
      //  トリガを引いていた時間が閾値を超えたのでリセット
      reset_game();
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
static void initializePins(void){
  pinMode(PIN_IN_TRIGGER, INPUT);
}

/**
 * @brief センタサーバルートGET処理
 * @param None
 * @return None
 */
static int get_root(void){
  const char* host = "192.168.100.114";
  
  DebugPrint("connecting to ");
  DebugPrint(host);
  
  WiFiClient client;
  const int Port = 5000;
  if (!client.connect(host, Port)) {
    DebugPrint("connection failed");
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
    DebugPrint(line.c_str());
    if(is_start_body){
      body += line;
    }
    if(line == ""){
      is_start_body = true;
    }
  }
  DebugPrint("");
  DebugPrint("body =");
  DebugPrint(body.c_str());
  DebugPrint("closing connection");
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
static int shoot(void){
  //  センタサーバに発射を通知し、的の判定を確認
  int target_num = get_root();
  DebugPrint("target_num = %d", target_num);
  //  弾数管理を更新する
  if(!ir_shooter.shoot()){
    DebugPrint("<ERROR> remain bullets is None");
  }
  DebugPrint("# shoot (remain bullets = %d)", ir_shooter.get_bullets_num());
  //  発射関係の演出を行う
  reactor.react_to_fire(ir_shooter.get_bullets_num());
  return target_num;
}

/**
 * @brief 得点時に行う一連の処理
 * @param None
 * @return None
 */
static void hit(void){
  //  得点間関係の演出を行う
  reactor.react_to_hit();
}

/**
 * @brief ピンレベルによる待機処理
 * @param[in] total_time_ms   特定ピン状態合計時間[ms]
 * @param[in] ref_pin         監視するピン番号
 * @param[in] delay_wait_ms   ピンレベルを読み取る間隔[ms]
 * @param[in] ref_level       HIGH or LOWどちらの状態の合計時間を記録するか
 * @return None
 * @note  ref_pinの状態がref_levelである時間の合計値がtotal_time_msに達するまで待機する\n
 *        ゲーム開始時、ゲーム終了後等で使う
 */
static void wait_by_pinlevel(int total_time_ms, int ref_pin, int delay_wait_ms, uint8_t ref_level){
  int total_push_time_ms = 0;
  bool is_pre_pushed = false;
  //  トリガを引いていた時間が閾値を超えるまでこのループにとどまり続ける
  while(total_push_time_ms < total_time_ms){
    if(digitalRead(ref_pin) == ref_level){
      if(is_pre_pushed){
        total_push_time_ms += delay_wait_ms;
      }else{
        is_pre_pushed = true;
      }
    }else{
      is_pre_pushed = false;
    }
    delay(delay_wait_ms);
  }
}

/**
 * @brief ゲームリセット
 * @param None
 * @return None
 */
static void reset_game(void){
  ir_shooter.reload();
  reactor.reset();
}