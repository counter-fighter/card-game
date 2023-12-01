#include "minion.h"

class NovicePyromancer : public Minion {
  NovicePyromancer(int player);
  ~NovicePyromancer();
  void activateAbility(Board &brd, Minion &target) override;
};