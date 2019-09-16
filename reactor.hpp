/**
 * @file reactor.hpp
 * @brief イベントに対する反応動作を管理するクラス
 */

#ifndef REACTOR_HPP
#define REACTOR_HPP

#include "display.hpp"
#include "speaker.hpp"
#include "vibrationMotor.hpp"

/**
 * @class Reactor
 * @brief
 */
class Reactor {
private:
  static unsigned char constexpr VOL = 0x10;
  Display display;
  Speaker speaker = Speaker(VOL);
  VibrationMotor vibrationMotor;

public:
  Reactor();
  void react_to_fire(int bullets_num);
  void react_to_hit();
  void sound_fire();
  void sound_hit();
  void vibrate(unsigned int time);
  void display_int(int disp_num);
};

#endif