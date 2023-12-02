#include "minion.h"

class MasterSummoner : public Minion {
  public :
    MasterSummoner(int player);
    ~MasterSummoner();
    void activateAbility(Board &brd) override;
};