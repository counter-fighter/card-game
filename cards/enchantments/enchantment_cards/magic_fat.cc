#include "magic_fat.h"

MagicFatigue::MagicFatigue() : Enchantment{"MagicFatigue", "Enchanted minion’s activated ability costs 2 more", 0} {};
MagicFatigue::~MagicFatigue() {};

void MagicFatigue::attach(Minion *target) {
  setActCost(target, target->getActivationCost() + 2);
};