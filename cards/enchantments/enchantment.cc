#include "enchantment.h"

Enchantment::Enchantment(string name, string desc, int cost) : Card{name, desc, cost} {};

Enchantment::~Enchantment() {};

void Enchantment::setAttack(Minion *target, int n) { target->atck = n; };
void Enchantment::setDefence(Minion *target, int n) { target->def = n; };
void Enchantment::setActReset(Minion *target, int n) { target->actReset = n; };
void Enchantment::setActCost(Minion *target, int n) { target->actCost = n; };