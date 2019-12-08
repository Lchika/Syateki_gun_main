/**
 * @file reactor.hpp
 * @brief イベントに対する反応動作を管理するクラス
 */

#ifndef REACTOR_HPP
#define REACTOR_HPP

#include "display.hpp"
#include "speaker.hpp"
#include "vibrationMotor.hpp"
#include "score.hpp"

/**
 * @class Reactor
 * @brief
 */
class Reactor {
private:
  static unsigned char constexpr VOL = 0x10;
  static constexpr uint8_t DISP_X = 14;
  static constexpr uint8_t DISP_Y = 10;
  Display display;
  Speaker speaker = Speaker(VOL);
  Score score;
  VibrationMotor vibrationMotor;
  void sound_fire();
  void sound_hit();

public:
  Reactor();
  Reactor(int initial_bullets_num);
  void react_to_fire(int bullets_num);
  void react_to_hit();
  void vibrate(unsigned int time);
  void display_int(int disp_num);
  void reset(int initial_bullets_num);
  void display_wait();
};

#endif