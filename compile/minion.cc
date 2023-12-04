#include "minion.h"
#include "player.h"

template<typename T> void moveVec (vector<T> &source, vector<T> &dest) {
  while (source.size() > 0) {
    auto it = source.begin();
    dest.push_back(move(*it));
    source.erase(it);
  }
};

Minion::Minion(string name, string desc, int cost, int player, int atck, int def, int actReset,int actCost) : 
  Card{name, desc, cost, player}, atck{atck}, atckReset{atck}, def{def}, defReset{def}, actCount(0), actReset{actReset}, actCost{actCost} {};

Minion::Minion(Minion &other): Card{other.name, other.desc, other.cost, other.player}, 
  atck{other.atck}, atckReset{atck}, def{other.def}, defReset{other.defReset}, 
  actCount{other.actCount}, actReset{other.actReset}, actCost{other.actCost} {
    moveVec(other.enchants, enchants);
}

Minion::Minion(Minion &&other): Card{other.name, other.desc, other.cost, other.player}, 
  atck{other.atck}, atckReset{atck}, def{other.def}, defReset{other.defReset}, 
  actCount{other.actCount}, actReset{other.actReset}, actCost{other.actCost} {
    moveVec(other.enchants, enchants);
}


Minion::~Minion() {};

void Minion::attack(Minion &target) {
  target.setDefence(target.getDefence() - atck);
  this->def -= target.getAttack();
  actCount--;
};

void Minion::attack(Player &target) {
  target.setPlayerHealth(target.getPlayerHealth() - atck);
  actCount--;
};

void Minion::setAttack(int n) { atck = n; };

void Minion::setDefence(int n) { def = n; };

void Minion::setAttackReset(int n) { atckReset = n; };

void Minion::setDefenceReset(int n) { defReset = n; };

void Minion::setActReset(int n) { actReset = n; };

void Minion::setActCost(int n) { actCost = n; };

int Minion::getActionCount() {
  return actCount;
};

void Minion::setActionCount(int n) {
  actCount = n;
};


int Minion::getAttack() const {
  return atck;
};

int Minion::getDefence() const {
  return def;
};

int Minion::getAttackReset() const {
  return atckReset;
};

int Minion::getDefenceReset() const {
  return defReset;
};

int Minion::getActivationCost() const {
  return actCost;
};

int Minion::getActionReset() const {
  return actReset;
};


CardType Minion::getCardType() const {
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

void Minion::detachEnchant () {

  Enchantment &temp = *enchants.back();
  temp.detach(*this);  
  enchants.pop_back();

  //enchants.erase(enchants.begin());
};

void Minion::detachAllEnchant () {
  int num = static_cast<int>(enchants.size());

  for (int i = 0; i < num; i++) {
    detachEnchant();
  }

};

vector<reference_wrapper<Enchantment>> Minion::getEnchantment() {
  vector<reference_wrapper<Enchantment>> ret;

  for (auto it = enchants.begin(); it != enchants.end(); it++) {
    ret.emplace_back(*(*it).get());
  }

  return ret;
};

TargetType Minion::getTargetType() const { return tt; }; 

