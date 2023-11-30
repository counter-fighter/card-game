#ifndef __BONEGOLEM_H__
#define __BONEGOLEM_H__
#include "minion.h"

class BoneGolem : public Minion {
    public:
        BoneGolem(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~BoneGolem();
        void notifyCardMinionLeave();
        void activateAbility();
}


#endif
