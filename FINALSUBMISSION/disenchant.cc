#include "disenchant.h"

Disenchant::Disenchant(int player) : Spell{"Disenchant", "Destroy top enchantment on target minion", 1, player, TargetType::MinionTarget} {};

Disenchant::~Disenchant() {};

// Only detaches enchanment if target is a minion
void Disenchant::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    Minion &m = static_cast<Minion&>(target);
    if (m.getEnchantment().size() == 0) {
      throw std::logic_error("Failed to remove enchantment. No enchantments exist on " + target.getName() + ".");
    }
    m.detachEnchant();
  }
};
