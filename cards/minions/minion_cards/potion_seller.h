#include "minion.h"

class PotionSeller : public Minion {
  PotionSeller();
  ~PotionSeller();
  void notifyCardTurnEnd(Board &brd) override;
};