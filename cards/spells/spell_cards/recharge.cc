#include "recharge.h"

Recharge::Recharge(int player) : Spell{"Recharge", "Your ritual gains 3 charges", 1, player, TargetType::RitualTarget} {};

Recharge::~Recharge() {};

void Recharge::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Ritual) {
    Ritual &r = dynamic_cast<Ritual&>(target);
    
    if (r.getPlayer() == this->getPlayer()) {
      r.setCharges(r.getCharges() + 3);
    }
  }
};