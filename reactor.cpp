#include "reactor.hpp"

Reactor::Reactor(){
  _set_frame();
  _set_title();
};

Reactor::Reactor(int initial_bullets_num){
  reset_display(initial_bullets_num);
};

void Reactor::react_to_fire(int bullets_num){
  //display.clear_display();
  display.clear_column_vertical(_column_bullet, _frame_width, 2, _margin_number_y, false);
  _display_int_on_column(bullets_num, _number_size, _column_bullet, _color_bullet);
  sound_fire();
  vibrationMotor.on(200);
}

void Reactor::react_to_hit(){
  score.up();
  sound_hit();
  display.clear_column_vertical(_column_score, _frame_width, 2, _margin_number_y, false);
  _display_int_on_column(score.get(), _number_size, _column_score, _color_score);
  //display.show_important_msg(0, 20, 2, String(score.get()) + " Hit!");
  //delay(500);
}

void Reactor::sound_fire(){
  speaker.play_file(0x01);
}

void Reactor::sound_hit(){
  speaker.play_file(0x02);
}

void Reactor::vibrate(unsigned int time){

}

void Reactor::display_int(int disp_num){
  //display.clear_display();
  int x_for_center = DISP_X;
  if(disp_num < 10 && disp_num > -1){
    x_for_center += 18;
  }
  //display.show_int(x_for_center, DISP_Y, disp_num);
}

void Reactor::reset(int initial_bullets_num){
  //display.clear_display();
  //display_int(initial_bullets_num);
  _update_display_nums(initial_bullets_num);
  score.reset();
}

void Reactor::display_wait(){
  display.clear_display();
  display.show_msg(0, 20, 1, "waiting response...", LED_BLUE_MEDIUM);
}

void Reactor::reset_display(int bullets_num)
{
  display.clear_display();
  _set_frame();
  _set_title();
  _update_display_nums(bullets_num);
}

void Reactor::_set_frame()
{
  display.show_column_frame(_frame_width, 2, LED_GREEN_MEDIUM);
}

void Reactor::_set_title()
{
  display.show_msg_on_column(0, _frame_width, 2, _margin_title, _margin_title, _title_size, "Score", LED_GREEN_MEDIUM);
  display.show_msg_on_column(1, _frame_width, 2, _margin_title, _margin_title, _title_size, "Bullet", LED_GREEN_MEDIUM);
}

void Reactor::_display_int_on_column(int16_t disp_num, uint8_t font_size, uint8_t column, uint16_t color)
{
  display.show_int_on_column(column, _frame_width, 2, _margin_number_x, _margin_number_y, font_size, disp_num, color);
}

void Reactor::_update_display_nums(int bullets_num)
{
  display.clear_column_vertical(_column_bullet, _frame_width, 2, _margin_number_y, false);
  _display_int_on_column(bullets_num, _number_size, _column_bullet, _color_bullet);
  display.clear_column_vertical(_column_score, _frame_width, 2, _margin_number_y, false);
  _display_int_on_column(0, _number_size, _column_score, _color_score);
}