#include "blizzard.h"
#include "board.h"

Blizzard::Blizzard(int player) : Spell{"Blizzard", "Deal 2 damage to all minions", 3, player, TargetType::NoTarget} {};

Blizzard::~Blizzard() {};

void Blizzard::useSpell(Board &brd) {
  brd.damageAll(2);
};

