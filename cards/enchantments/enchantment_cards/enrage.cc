#include "enrage.h"

Enrage::Enrage() : Enchantment{"Enrage", "*2/*2", 2} {};
Enrage::~Enrage() {};

void Enrage::attach(Minion *target) {
  setAttack(target, target->getAttack() * 2);
  setDefence(target, target->getDefence() * 2);
};