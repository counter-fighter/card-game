#include "aura_of_power.h"

AuraOfPower::AuraOfPower(int player) : Ritual{"Aura of Power", "", 1, player, 4, 1} {};

AuraOfPower::~AuraOfPower() {};

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

