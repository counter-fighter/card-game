#include "minion.h"

class BoneGolem : public Minion {
  void notifyCardMinionLeave(Board &brd, Card &target) override;
  
  public :
    BoneGolem(int player);
    ~BoneGolem();
};