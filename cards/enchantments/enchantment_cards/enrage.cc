#include "enrage.h"

Enrage::Enrage(int player) : Enchantment{"Enrage", "*2/*2", 2, player} {};
Enrage::~Enrage() {};

void Enrage::attach(Minion &target) {
  target.setAttack(target.getAttack() * 2);
  target.setDefence(target.getDefence() * 2);
};