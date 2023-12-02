#include "blizzard.h"

Blizzard::Blizzard(int player) : Spell{"Blizzard", "Deal 2 damage to all minions", 3, player, TargetType::NoTarget} {};

Blizzard::~Blizzard() {};

bool Blizzard::useSpell(Board &brd, Card &target) {
  //brd.damageAll(2);
  return true;
};

