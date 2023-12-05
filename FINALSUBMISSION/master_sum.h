#ifndef __MASTER_SUM_H__
#define __MASTER_SUM_H__
#include "minion.h"
#include "board.h"

class MasterSummoner : public Minion {
  public :
    MasterSummoner(int player);
    ~MasterSummoner();
    void activateAbility(Board &brd) override;
};

#endif 
