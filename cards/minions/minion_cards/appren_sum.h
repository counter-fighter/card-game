#include "minion.h"

class ApprenticeSummoner : public Minion {
  ApprenticeSummoner();
  ~ApprenticeSummoner();
  void activateAbility(Board &brd) override;
};