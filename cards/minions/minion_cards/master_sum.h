#include "minion.h"

class MasterSummoner : public Minion {
  MasterSummoner(int player);
  ~MasterSummoner();
  void activateAbility(Board &brd) override;
};