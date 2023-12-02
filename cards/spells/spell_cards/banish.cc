#include "banish.h"

Banish::Banish(int player) : Spell{"Banish", "Destroy target minion or ritual", 2, player, TargetType::AllTarget} {};

Banish::~Banish() {};

void Banish::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    m.setDefence(-1);
  } else {
    // brd.removeRitual();
  }

};
