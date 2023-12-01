#include "silence.h"

Silence::Silence() : Enchantment{"Silence", "Enchanted minion cannot use abilities", 1} {};
Silence::~Silence() {};

void Silence::attach(Minion *target) {
  setActReset(target, -1);
};