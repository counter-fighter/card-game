#include "unsummon.h"

Unsummon::Unsummon(int player) : Spell{"Unsummon", "Return target minion to its owner\'s hand", 1, player, TargetType::MinionTarget} {};

Unsummon::~Unsummon() {};

void Unsummon::useSpell(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion) {
    target.setReturnToHand(true);
  }
};
