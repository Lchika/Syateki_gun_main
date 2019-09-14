/**
 * @file vibrationMotor.hpp
 * @brief 振動モータクラス
 */

#ifndef VIBRATION_MOTOR_HPP
#define VIBRATION_MOTOR_HPP

#include <Arduino.h>

/**
 * @class VibrationMotor
 * @brief
 */
class VibrationMotor {
private:
  int _pin = 19;
  void set_pin_mode();

public:
  VibrationMotor();
  VibrationMotor(int pin);
  void on(unsigned int time_ms);
};

#endif