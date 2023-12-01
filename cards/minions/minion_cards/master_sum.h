#include "minion.h"

class MasterSummoner : public Minion {
  MasterSummoner();
  ~MasterSummoner();
  void activateAbility(Board &brd) override;
};