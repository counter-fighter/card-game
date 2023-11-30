#include "minion.h"

Minion::Minion(string name, string desc, int cost, int atck, int def, int actCount, int actReset,int actCost) : 
  Card{name, desc, cost}, atck{atck}, def{def}, actCount(actCount), actReset{actReset}, actCost{actCost} {};
Minion::~Minion() {};

void Minion::attack(Minion &target) {
  target.setDefence(target.getDefence() - this->atck);
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

int Minion::getDefence() {
  return def;
};

int Minion::getActivationCost() {
  return actCost;
};

CardType Minion::getCardType() {
  return ct;
}; //Card type already determined
