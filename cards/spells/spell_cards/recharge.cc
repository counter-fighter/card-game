#include "recharge.h"

Recharge::Recharge(int player) : Spell{"Recharge", "Your ritual gains 3 charges", 1, player, TargetType::NoTarget} {};

Recharge::~Recharge() {};

void Recharge::useSpell(Board &brd) {
  //brd.recharge(player, 3);
};