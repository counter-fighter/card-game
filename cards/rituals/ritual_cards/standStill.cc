#include "standStill.h"

StandStill::StandStill(int player) : Ritual{"Stand Still", "Whenever a minion enters play, destroy it", 3, player, 4, 2} {};

StandStill::~StandStill() {};

void StandStill::notifyCardMinionEnter(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    m.setDefence(-1);
  }
};

