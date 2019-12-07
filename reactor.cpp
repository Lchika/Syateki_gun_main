#include "reactor.hpp"

Reactor::Reactor(){
};

Reactor::Reactor(int initial_bullets_num){
  display.clear_display();
  display_int(initial_bullets_num);
};

void Reactor::react_to_fire(int bullets_num){
  display.clear_display();
  display_int(bullets_num);
  sound_fire();
  vibrationMotor.on(200);
}

void Reactor::react_to_hit(){
  score.up();
  sound_hit();
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
  int x_for_center = DISP_X;
  if(disp_num < 10 && disp_num > -1){
    x_for_center += 18;
  }
  display.show_int(x_for_center, DISP_Y, disp_num);
}

void Reactor::reset(int initial_bullets_num){
  display.clear_display();
  display_int(initial_bullets_num);
  score.reset();
}