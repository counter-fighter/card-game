#include "silence.h"

Silence::Silence(int player) : Enchantment{"Silence", "Enchanted minion cannot use abilities", 1, player} {};
Silence::~Silence() {};

void Silence::attach(Minion &target) {
  target.setActReset(-1);
};