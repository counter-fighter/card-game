#include "master_sum.h"

MasterSummoner::MasterSummoner(int player) : Minion{"Master Summoner", "Summon a 1/1 air elemental", 3, player, 2, 3, 1, 2} {};

MasterSummoner::~MasterSummoner() {};

void MasterSummoner::activateAbility(Board &brd) {
  brd.summon("Air Elemental", 3, player);
  actCount -= actCost;
};
