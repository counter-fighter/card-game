#include "appren_sum.h"

ApprenticeSummoner::ApprenticeSummoner(int player) : Minion{"Apprentice Summoner", "Summon a 1/1 air elemental", 1, player, 1, 1, 1, 1} {};

ApprenticeSummoner::~ApprenticeSummoner() {};

void ApprenticeSummoner::activateAbility(Board &brd) {
  int psuedoCost = (actCount > 0)? actCost : -1;
  if (brd.summon("Air Elemental", 1, player, psuedoCost)) actCount--;
};
