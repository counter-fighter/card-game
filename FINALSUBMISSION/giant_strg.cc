#include "giant_strg.h"

GiantStrength::GiantStrength(int player) : Enchantment{"Giant Strength", "", 1, player, "+2", "+2"} {};
GiantStrength::~GiantStrength() {};

void GiantStrength::attach(Minion &target) {
  target.setAttack(target.getAttack() + 2);
  target.setDefence(target.getDefence() + 2);
  target.setAttackReset(target.getAttackReset() + 2);
  target.setDefenceReset(target.getDefenceReset() + 2);
};

void GiantStrength::detach(Minion &target) {
  target.setAttackReset(target.getAttackReset() - 2);
  target.setDefenceReset(target.getDefenceReset() - 2);

  if (target.getAttack() > target.getAttackReset()) {
    target.setAttack(target.getAttackReset());
  }

  if (target.getDefence() > target.getDefenceReset()) {
    target.setDefence(target.getDefenceReset());
  }
};