#include "spell.h"

Spell::Spell(string name, string desc, int cost, int player) : Card{name, desc, cost, player} {};

Spell::~Spell() {};

CardType Spell::getCardType() { return ct; };