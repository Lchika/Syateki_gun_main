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
  static constexpr uint8_t _frame_width = 2;
  static constexpr uint8_t _margin_title = 3;
  static constexpr uint8_t _title_size = 1;
  static constexpr uint8_t _margin_number_x = 5;
  static constexpr uint8_t _margin_number_y = 25;
  static constexpr uint8_t _number_size = 3;
  static constexpr uint8_t _column_score = 0;
  static constexpr uint8_t _column_bullet = 1;
  static constexpr uint16_t _color_score = LED_RED_HIGH;
  static constexpr uint16_t _color_bullet = LED_BLUE_HIGH;
  Display display;
  Speaker speaker = Speaker(VOL);
  Score score;
  VibrationMotor vibrationMotor;
  void sound_fire();
  void sound_hit();
  void _set_frame();
  void _set_title();
  void _display_int_on_column(int16_t disp_num, uint8_t font_size, uint8_t column, uint16_t color = LED_RED_HIGH);
  void _clear_number_area(int16_t column);
  void _update_display_nums(int bullets_num);

public:
  Reactor();
  Reactor(int initial_bullets_num);
  void react_to_fire(int bullets_num);
  void react_to_hit();
  void vibrate(unsigned int time);
  void display_int(int disp_num);
  void reset(int initial_bullets_num);
  void display_wait();
  void reset_display(int bullets_num);
};

#endif