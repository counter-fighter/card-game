#include "minion.h"

Minion::Minion(string name, string desc, int cost, int player, int atck, int def, int actReset,int actCost) : 
  Card{name, desc, cost, player}, atck{atck}, def{def}, actCount(0), actReset{actReset}, actCost{actCost} {};
Minion::~Minion() {};

void Minion::attack(Minion &target) {
  target.setDefence(target.getDefence() - this->atck);
  this->def = this->def - target.getAttack();
  actCount--;
};

void Minion::attack(Player &target) {
// Awaiting player implementation
};

void Minion::setAttack(int n) { atck = n; };

void Minion::setDefence(int n) { def = n; };

void Minion::setActReset(int n) { actReset = n; };

void Minion::setActCost(int n) { actCost = n; };

int Minion::getActionCount() {
  return actCount;
};

int Minion::getAttack() {
  return atck;
};

int Minion::getDefence() {
  return def;
};

int Minion::getActivationCost() {
  return actCost;
};

int Minion::getActionReset() {
  return actReset;
};


CardType Minion::getCardType() {
  return ct;
}; //Card type already determined

void Minion::activateAbility(Board &brd) {};

void Minion::activateAbility(Board &brd, Minion &target) {};


void Minion::notifyCardTurnStart(Board &brd) {
  actCount = actReset;
};


void Minion::attachEnchant (unique_ptr<Enchantment> ench) {
  ench->attach(*this);
  enchants.emplace_back(move(ench));

};
