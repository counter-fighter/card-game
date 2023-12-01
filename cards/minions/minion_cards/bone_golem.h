#include "minion.h"

class BoneGolem : public Minion {
  BoneGolem(int player);
  ~BoneGolem();
  void notifyCardMinionLeave(Board &brd, Card &target) override;
};