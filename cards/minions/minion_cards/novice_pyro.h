#include "minion.h"

class NovicePyromancer : public Minion {
  NovicePyromancer();
  ~NovicePyromancer();
  void activateAbility(Minion &target) override;
};