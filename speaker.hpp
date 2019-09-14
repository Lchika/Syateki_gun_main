/**
 * @file speaker.hpp
 * @brief 音声出力クラス
 */

#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include <Arduino.h>

/**
 * @class Speaker
 * @brief
 */
class Speaker {
private:
  HardwareSerial serial_voice_module = HardwareSerial(2);

public:
  Speaker(unsigned char vol);
  void play_file(unsigned char file_num);
};

#endif