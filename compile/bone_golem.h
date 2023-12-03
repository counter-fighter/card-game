#ifndef __BONEGOLEM_H__
#define __BONEGOLEM_H__
#include "minion.h"

class BoneGolem : public Minion {
  void notifyCardMinionLeave(Board &brd, Card &target) override;
  
  public :
    BoneGolem(int player);
    ~BoneGolem();
};

#endif
