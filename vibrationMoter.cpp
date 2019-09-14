#include "vibrationMotor.hpp"

VibrationMotor::VibrationMotor(){
  set_pin_mode();
};

VibrationMotor::VibrationMotor(int pin)
  :_pin(pin)
{
  set_pin_mode();
};

void VibrationMotor::on(unsigned int time_ms){
  digitalWrite(_pin, HIGH);
  delay(time_ms);
  digitalWrite(_pin, LOW);
}

void VibrationMotor::set_pin_mode(){
  digitalWrite(_pin, LOW);
  pinMode(_pin, OUTPUT);
}