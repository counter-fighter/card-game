#include "master_sum.h"

MasterSummoner::MasterSummoner(int player) : Minion{"Master Summoner", "Summon up to three 1/1 air elementals", 3, player, 2, 3, 1, 2} {};

MasterSummoner::~MasterSummoner() {};

void MasterSummoner::activateAbility(Board &brd) {
  int psuedoCost = (actCount >= actCost)? actCost : -1;
  if (brd.summon("Air Elemental", 3, player, psuedoCost)) actCount -= actCost;
};
