#include "minion.h"

class PotionSeller : public Minion {
  public :
    PotionSeller(int player);
    ~PotionSeller();
    void notifyCardTurnEnd(Board &brd) override;
};