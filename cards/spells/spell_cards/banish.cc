#include "banish.h"

Banish::Banish(int player) : Spell{"Banish", "Destroy target minion or ritual", 2, player} { requireTarget = true; };

Banish::~Banish() {};

bool Banish::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    m.setDefence(-1);
    return true;
  }

  if (target.getCardType() == CardType::Ritual) {
    // brd.removeRitual();
    return true;
  }

    return false;
};
