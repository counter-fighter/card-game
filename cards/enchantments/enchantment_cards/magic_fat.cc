#include "magic_fat.h"

MagicFatigue::MagicFatigue(int player) : Enchantment{"MagicFatigue", "Enchanted minion’s activated ability costs 2 more", 0, player} {};
MagicFatigue::~MagicFatigue() {};

void MagicFatigue::attach(Minion &target) {
  target.setActCost(target.getActivationCost() + 2);
};