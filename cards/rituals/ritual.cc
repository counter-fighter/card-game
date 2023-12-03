#include "ritual.h"

Ritual::Ritual(string name, string desc, int cost, int player, int charges, int actCost) : Card{name, desc, cost, player}, actCost{actCost}, charges{charges} {};

Ritual::~Ritual() {};

CardType Ritual::getCardType() { return ct; };

TargetType Ritual::getTargetType() { return tt; }; 

int Ritual::getCharges() { return charges; };

void Ritual::setCharges(int n) { charges = n; };

int Ritual::getActionCost() { return actCost; };
