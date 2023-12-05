#include "aura_of_power.h"

AuraOfPower::AuraOfPower(int player) : Ritual{"Aura of Power", "Whenever a minion enters play under your control, it gains +1/+1", 1, player, 4, 1} {};

AuraOfPower::~AuraOfPower() {};

// Checks that this ritual has enough charges, and that target is of right 
//   type from opposing player, otherwise does not run
void AuraOfPower::notifyCardMinionEnter(Board &brd, Card &target) {
  if (target.getCardType() == CardType::Minion && charges >= actCost) {
    Minion &m = dynamic_cast<Minion&>(target);

    if (m.getPlayer() == this->getPlayer()) {
      m.setAttack(m.getAttack() + 1);
      m.setDefence(m.getDefence() + 1);
      charges -= actCost;
    }
  }
};

