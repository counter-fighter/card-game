#include "silence.h"

Silence::Silence(int player) : Enchantment{"Silence", "Enchanted minion cannot use abilities", 1, player} {};
Silence::~Silence() {};

void Silence::attach(Minion &target) {
  int actReset = target.getActionReset();
  if (actReset > 0) {
    target.setActReset(-actReset);
  }
};

void Silence::detach(Minion &target) {
  int actReset = target.getActionReset();
  if (actReset < 0) {
    target.setActReset(-actReset);
  }
};
