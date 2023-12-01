#include "giant_strg.h"

GiantStrength::GiantStrength() : Enchantment{"Giant Strength", "+2/+2", 1} {};
GiantStrength::~GiantStrength() {};

void GiantStrength::attach(Minion *target) {
  setAttack(target, target->getAttack() + 2);
  setDefence(target, target->getDefence() + 2);
};