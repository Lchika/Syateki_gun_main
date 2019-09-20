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
  WiFi.begin("your-SSID", "your-PASSWORD");
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
        get_root();
        ir_shooter.shoot();
        Serial.println("# shoot (remain bullets = " + String(ir_shooter.get_bullets_num()) + ")");
        reactor.react_to_fire(ir_shooter.get_bullets_num());
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

static void get_root(){
  const char* host      = "192.168.100.114";
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  WiFiClient client;
  const int Port = 5000;
  if (!client.connect(host, Port)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" + 
    "Connection: close\r\n\r\n");
  delay(1000);

  // 返ってきた情報の解析
  while(client.available()){
    String line = client.readStringUntil('\r');
    line.trim();
    Serial.println(line);
  }
  Serial.println();
  Serial.println("closing connection");
}