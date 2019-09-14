/**
 * @file speaker.hpp
 * @brief 音声出力クラス
 */

#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include <DFRobotDFPlayerMini.h>

/**
 * @class Speaker
 * @brief
 */
class Speaker {
private:
  SoftwareSerial *softwareSerial;
  DFRobotDFPlayerMini dFPlayer;

public:
  Speaker();
  void sound_file(unsigned int file_num);
};

#endif