/**
 * @file score.hpp
 * @brief スコアを管理するクラス
 */

#ifndef SCORE_HPP
#define SCORE_HPP

/**
 * @class Score
 * @brief
 */
class Score {
private:
  static unsigned int constexpr INI_SCORE = 0;
  unsigned int score = INI_SCORE;

public:
  Score();
  Score(unsigned int ini_score);
  void up(void);
  unsigned int get(void);
  void reset(void);
};

#endif