#ifndef __NOVICEPYROMANCER_H__
#define __NOVICEPYROMANCER_H__
#include "minion.h"

class NovicePyromancer : public Minion {
  public :
    NovicePyromancer(int player);
    ~NovicePyromancer();
    void activateAbility(Board &brd, Minion &target) override;
};

#endif
