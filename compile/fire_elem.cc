#include "fire_elem.h"

FireElemental::FireElemental(int player) : Minion{"Fire Elemental", "Whenever an opponent\'s minion enters play, deal 1 damage to it", 2, player, 2, 2, 1, 0} {};

FireElemental::~FireElemental() {};

void FireElemental::notifyCardMinionEnter(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    if (m.getPlayer() != player) {
      m.setDefence(m.getDefence() - 1);
    }
  }
};
