#include "haste.h"

Haste::Haste(int player) : Enchantment{"Haste", "Enchanted minion gains +1 action each turn", 1, player} {};
Haste::~Haste() {};

void Haste::attach(Minion &target) {
  target.setActReset(target.getActionReset() + 1);
};