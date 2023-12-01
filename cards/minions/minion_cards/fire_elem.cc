#include "fire_elem.h"

FireElement::FireElement(int player) : Minion{"Fire Element", "Whenever an opponent’s minion enters play, deal 1 damage to it", 2, player, 2, 2, 1, 0} {};

FireElement::~FireElement() {};

void FireElement::notifyCardMinionLeave(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    m.setDefence(m.getAttack() - 1);

  }
};
