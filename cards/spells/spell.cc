#include "spell.h"

Spell::Spell(string name, string desc, int cost, int player, TargetType tt) : Card{name, desc, cost, player}, tt{tt} {};

Spell::~Spell() {};

CardType Spell::getCardType() { return ct; };

TargetType Spell::getTargetType() { return tt; }; 

void Spell::useSpell(Board &brd, Card &target) {};

void Spell::useSpell(Board &brd) {};
