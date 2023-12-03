#ifndef __POTION_SELLER_H__
#define __POTION_SELLER_H__
#include "minion.h"

class PotionSeller : public Minion {
  public :
    PotionSeller(int player);
    ~PotionSeller();
    void notifyCardTurnEnd(Board &brd) override;
};

#endif
