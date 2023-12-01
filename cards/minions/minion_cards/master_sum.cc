#include "master_sum.h"

MasterSummoner::MasterSummoner(int player) : Minion{"Apprentice Summoner", "Summon a 1/1 air elemental", 3, player, 2, 3, 1, 2} {};

MasterSummoner::~MasterSummoner() {};

void MasterSummoner::activateAbility(Board &brd) {
  // brd.summon(3, "Air Element")
};
