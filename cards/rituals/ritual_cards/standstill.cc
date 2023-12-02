#include "standstill.h"

Standstill::Standstill(int player) : Ritual{"Stand Still", "Whenever a minion enters play, destroy it", 3, player, 4, 2} {};

Standstill::~Standstill() {};

void Standstill::notifyCardMinionEnter(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    m.setDefence(-1);
  }
};

