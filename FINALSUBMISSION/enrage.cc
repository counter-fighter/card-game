#include "enrage.h"

Enrage::Enrage(int player) : Enchantment{"Enrage", "*2/*2", 2, player, "*2", "*2"} {};
Enrage::~Enrage() {};

void Enrage::attach(Minion &target) {
  target.setAttack(target.getAttack() * 2);
  target.setDefence(target.getDefence() * 2);
  target.setAttackReset(target.getAttackReset() * 2);
  target.setDefenceReset(target.getDefenceReset() * 2);
};

void Enrage::detach(Minion &target) {
  target.setAttackReset(target.getAttackReset() / 2);
  target.setDefenceReset(target.getDefenceReset() / 2);

  if (target.getAttack() > target.getAttackReset()) {
    target.setAttack(target.getAttackReset());
  }

  if (target.getDefence() > target.getDefenceReset()) {
    target.setDefence(target.getDefenceReset());
  }
};
