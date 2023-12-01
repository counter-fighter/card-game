#include "appren_sum.h"

ApprenticeSummoner::ApprenticeSummoner() : Minion{"Apprentice Summoner", "Summon a 1/1 air elemental", 1, 1, 1, 1, 1} {};

ApprenticeSummoner::~ApprenticeSummoner() {};

void ApprenticeSummoner::activateAbility(Board &brd) {
  // brd.summon(1, "Air Element")
};
