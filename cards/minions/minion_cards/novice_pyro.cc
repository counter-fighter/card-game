#include "novice_pyro.h"

NovicePyromancer::NovicePyromancer() : Minion{"Novice Pyromancer", "Deal 1 damage to target minion", 1, 0, 1, 1, 1} {};

NovicePyromancer::~NovicePyromancer() {};

void NovicePyromancer::activateAbility(Minion &target) {
  target.minusDefence(1);
};
