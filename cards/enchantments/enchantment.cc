#include "enchantment.h"

Enchantment::Enchantment(string name, string desc, int cost, int player) : Card{name, desc, cost, player} {};

Enchantment::~Enchantment() {};

CardType Enchantment::getCardType() {
  return ct;
}; 
