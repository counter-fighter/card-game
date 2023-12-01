#include "raiseDead.h"

RaiseDead::RaiseDead(int player) : Spell{"Raise Dead", "Resurrect the top minion in your graveyard and set its defense to 1", 1, player} {};

RaiseDead::~RaiseDead() {};

bool RaiseDead::useSpell(Board &brd, Card &target) {
  //brd.raiseDead();
  //return true;

};

