#include "unsummon.h"

Unsummon::Unsummon(int player) : Spell{"Unsummon", "Return target minion to its owner’s hand", 1, player} {};

Unsummon::~Unsummon() {};

bool Unsummon::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    m.setDefence(-1000000);
    return true;
  }
  return false;

};
