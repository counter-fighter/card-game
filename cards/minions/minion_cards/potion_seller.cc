#include "potion_seller.h"

PotionSeller::PotionSeller() : Minion{"Potion Seller", "At the end of your turn, all your minions gain +0/+1", 2, 1, 3, 1, 0} {};

PotionSeller::~PotionSeller() {};

void PotionSeller::notifyCardTurnEnd(Board &brd) {
  // brd.healAll(1);
};
