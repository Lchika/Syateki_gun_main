#include "reactor.hpp"

Reactor::Reactor(){
};


void Reactor::sound_fire(){

}

void Reactor::sound_hit(){

}

void Reactor::vibrate(unsigned int time){

}

void Reactor::display_int(int disp_num){
  display.show_int(0, 0, disp_num);
}