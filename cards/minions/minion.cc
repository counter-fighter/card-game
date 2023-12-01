#include "minion.h"

Minion::Minion(string name, string desc, int cost, int atck, int def, int actReset,int actCost) : 
  Card{name, desc, cost}, atck{atck}, def{def}, actCount(0), actReset{actReset}, actCost{actCost} {};
Minion::~Minion() {};

void Minion::attack(Minion &target) {
  target.minusDefence(this->atck);
  this->def = this->def - target.getAttack();
  actCount--;
};

void Minion::attack(Player &target) {
// Awaiting player implementation
};

int Minion::getActionCount() {
  return actCount;
};

int Minion::getAttack() {
  return atck;
};

void Minion::minusDefence(int n) {
  this->def -= n;
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
  enchants.emplace_back(ench);
  Enchantment* temp = ench.get();
  temp->attach(this);

};
