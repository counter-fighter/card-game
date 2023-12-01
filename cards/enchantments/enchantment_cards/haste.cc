#include "haste.h"

Haste::Haste() : Enchantment{"Haste", "Enchanted minion gains +1 action each turn", 1} {};
Haste::~Haste() {};

void Haste::attach(Minion *target) {
  setActReset(target, target->getActionReset() + 1);
};