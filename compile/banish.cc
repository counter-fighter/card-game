#include "banish.h"
#include "board.h"

Banish::Banish(int player) : Spell{"Banish", "Destroy target minion or ritual", 2, player, TargetType::AllTarget} {};

Banish::~Banish() {};

// Only kills target directly if target is minion, otherwise passed to removeRitual
void Banish::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = static_cast<Minion&>(target);

    m.setDefence(-1);
  } else {
    brd.removeRitual(target.getPlayer());
  }

};
