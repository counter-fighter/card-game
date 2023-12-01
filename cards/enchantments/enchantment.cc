#include "enchantment.h"

Enchantment::Enchantment(string name, string desc, int cost, int player, string atck = "", string def = "") : Card{name, desc, cost, player}, atck{atck}, def{def} {};

Enchantment::~Enchantment() {};

CardType Enchantment::getCardType() {
  return ct;
}; 

string Enchantment::getAttack() { return atck; };
string Enchantment::getDefence() { return def; };
