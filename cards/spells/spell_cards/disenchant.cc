#include "disenchant.h"

Disenchant::Disenchant(int player) : Spell{"Disenchant", "Destroy top enchantment on target minion", 1, player} { requireTarget = true; };

Disenchant::~Disenchant() {};

bool Disenchant::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);

    m.detachEnchant();
    return true;
  }
  
  return false;

};
