#include "magic_fat.h"

MagicFatigue::MagicFatigue(int player) : Enchantment{"MagicFatigue", "Enchanted minion\'s activated ability costs 2 more", 0, player} {};
MagicFatigue::~MagicFatigue() {};

void MagicFatigue::attach(Minion &target) {
  if (target.getActivationCost() != 0)
    target.setActCost(target.getActivationCost() + 2);
};

void MagicFatigue::detach(Minion &target) {
  if (target.getActivationCost() != 0)
    target.setActCost(target.getActivationCost() - 2);
};
