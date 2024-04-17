#include "haste.h"

Haste::Haste(int player) : Enchantment{"Haste", "Enchanted minion gains +1 action each turn", 1, player} {};
Haste::~Haste() {};

void Haste::attach(Minion &target) {
  int actReset = target.getActionReset();
  if (actReset < 0) {
    target.setActReset(actReset - 1);
  } else {
    target.setActReset(actReset + 1);
  }
};

void Haste::detach(Minion &target) {
  int actReset = target.getActionReset();
  if (actReset < 0) {
    target.setActReset(actReset + 1);
  } else {
    target.setActReset(actReset - 1);
  }
  
  if (target.getActionCount() > target.getActionReset()) {
    target.setActionCount(target.getActionReset());
  }
};
