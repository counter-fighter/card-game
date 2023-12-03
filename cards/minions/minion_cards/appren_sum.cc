#include "appren_sum.h"

ApprenticeSummoner::ApprenticeSummoner(int player) : Minion{"Apprentice Summoner", "Summon a 1/1 air elemental", 1, player, 1, 1, 1, 1} {};

ApprenticeSummoner::~ApprenticeSummoner() {};

void ApprenticeSummoner::activateAbility(Board &brd) {
  brd.summon("Air Elemental", 1, player);
  this->actCount--;
};
