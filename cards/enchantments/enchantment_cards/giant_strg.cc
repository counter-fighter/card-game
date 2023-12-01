#include "giant_strg.h"

GiantStrength::GiantStrength(int player) : Enchantment{"Giant Strength", "+2/+2", 1, player} {};
GiantStrength::~GiantStrength() {};

void GiantStrength::attach(Minion &target) {
  target.setAttack(target.getAttack() + 2);
  target.setDefence(target.getDefence() + 2);
};