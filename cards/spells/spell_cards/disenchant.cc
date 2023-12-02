#include "disenchant.h"

Disenchant::Disenchant(int player) : Spell{"Disenchant", "Destroy top enchantment on target minion", 1, player, TargetType::MinionTarget} {};

Disenchant::~Disenchant() {};

void Disenchant::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = dynamic_cast<Minion&>(target);
    m.detachEnchant();
  }
};
