#include "reactor.hpp"

Reactor::Reactor(){
};

void Reactor::react_to_fire(int bullets_num){
  display.clear_display();
  display.show_int(0, 0, bullets_num);
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
  display.show_int(0, 0, disp_num);
}

void Reactor::reset(){
  display.clear_display();
  score.reset();
}