#include "spell.h"

Spell::Spell(string name, string desc, int cost, int player, TargetType tt) : Card{name, desc, cost, player}, tt{tt} {};

Spell::~Spell() {};

CardType Spell::getCardType() const { return ct; };

TargetType Spell::getTargetType() const { return tt; }; 

void Spell::useSpell(Board &brd, Card &target) {};

void Spell::useSpell(Board &brd) {};
