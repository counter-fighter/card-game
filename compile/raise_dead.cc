#include "raise_dead.h"

RaiseDead::RaiseDead(int player) : Spell{"Raise Dead", "Resurrect the top minion in your graveyard and set its defense to 1", 1, player, TargetType::NoTarget} {};

RaiseDead::~RaiseDead() {};

void RaiseDead::useSpell(Board &brd) {
  brd.raiseDead(player);
};

