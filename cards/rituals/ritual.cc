#include "ritual.h"

Ritual::Ritual(string name, string desc, int cost, int player, int actCost, int charges) : Card{name, desc, cost, player}, actCost{actCost}, charges{charges} {};

Ritual::~Ritual() {};

CardType Ritual::getCardType() { return ct; };

int Ritual::getCharges() { return charges; };

void Ritual::setCharges(int n) { charges = n; };

int Ritual::getActionCost() { return actCost; };
