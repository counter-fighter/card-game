#include "minion.h"

class ApprenticeSummoner : public Minion {
  ApprenticeSummoner(int player);
  ~ApprenticeSummoner();
  void activateAbility(Board &brd) override;
};