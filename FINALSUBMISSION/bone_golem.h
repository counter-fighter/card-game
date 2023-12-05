#ifndef __BONEGOLEM_H__
#define __BONEGOLEM_H__
#include "minion.h"

class BoneGolem : public Minion {
  public :
    BoneGolem(int player);
    ~BoneGolem();
    void notifyCardMinionLeave(Board &brd, Card &target) override; // Gain +1/+1 whenever a minion leaves play
};

#endif
