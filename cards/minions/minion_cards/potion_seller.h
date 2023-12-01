#include "minion.h"

class PotionSeller : public Minion {
  PotionSeller(int player);
  ~PotionSeller();
  void notifyCardTurnEnd(Board &brd) override;
};