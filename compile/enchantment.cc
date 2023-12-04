#include "enchantment.h"

Enchantment::Enchantment(string name, string desc, int cost, int player, string atck, string def) : 
Card{name, desc, cost, player}, atck{atck}, def{def} {};

Enchantment::~Enchantment() {};

CardType Enchantment::getCardType() const { return ct; }; 

TargetType Enchantment::getTargetType() const { return tt; }; 



string Enchantment::getAttack() const { return atck; };
string Enchantment::getDefence() const { return def; };
