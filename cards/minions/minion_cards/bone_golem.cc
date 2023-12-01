#include "bone_golem.h"

BoneGolem::BoneGolem() : Minion{"Bone Golem", "Gain +1/+1 whenever a minion leaves play", 2, 1, 3, 1, 0} {};

BoneGolem::~BoneGolem() {};

void BoneGolem::notifyCardMinionLeave(Board &brd, Card &target) {
  Minion::atck++;
  Minion::def++;
};
