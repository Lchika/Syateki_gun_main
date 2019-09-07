/**
 * @file irShooter.hpp
 * @brief 赤外線銃としての機能を管理するクラスヘッダ
 */

#ifndef IR_SHOOTER_HPP
#define IR_SHOOTER_HPP

/**
 * @class IrShooter
 * @brief 赤外線銃としての機能を管理するクラス
 */
class IrShooter {
private:

public:
  IrShooter();
  bool irOn();
  bool irOff();
  unsigned int getBulletsNum();
  void reload();
};

#endif