#include "novice_pyro.h"

NovicePyromancer::NovicePyromancer(int player) : Minion{"Novice Pyromancer", "Deal 1 damage to target minion", 1, player, 0, 1, 1, 1} {};

NovicePyromancer::~NovicePyromancer() {};

void NovicePyromancer::activateAbility(Board &brd, Minion &target) {
  target.setDefence(target.getDefence() - 1);
  this->actCount--;
};
