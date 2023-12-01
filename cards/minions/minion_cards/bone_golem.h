#include "minion.h"

class BoneGolem : public Minion {
  BoneGolem();
  ~BoneGolem();
  void notifyCardMinionLeave(Board &brd, Card &target) override;
};