#ifndef __FIREELEM_H__
#define __FIREELEM_H__
#include "minion.h"

class FireElemental : public Minion {
  public :
    FireElemental(int player);
    ~FireElemental();
    void notifyCardMinionEnter(Board &brd, Card &target) override;
};

#endif
