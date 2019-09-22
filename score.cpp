#include "score.hpp"

Score::Score(){
};

Score::Score(unsigned int ini_score):score(ini_score){
};

void Score::up(void){
  score++;
}

unsigned int Score::get(void){
  return score;
}

void Score::reset(void){
  score = INI_SCORE;
}