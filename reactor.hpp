/**
 * @file reactor.hpp
 * @brief イベントに対する反応動作を管理するクラス
 */

#ifndef REACTOR_HPP
#define REACTOR_HPP

#include "display.hpp"

/**
 * @class Reactor
 * @brief
 */
class Reactor {
private:
  Display display;

public:
  Reactor();
  void sound_fire();
  void sound_hit();
  void vibrate(unsigned int time);
  void display_int(int disp_num);
};

#endif