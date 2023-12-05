#ifndef __APPRENSUM_H__
#define __APPRENSUM_H__
#include "minion.h"
#include "board.h"

class ApprenticeSummoner : public Minion {
  public :
    ApprenticeSummoner(int player);
    ~ApprenticeSummoner();
    void activateAbility(Board &brd) override; // Summon a 1/1 air elemental
};

#endif
