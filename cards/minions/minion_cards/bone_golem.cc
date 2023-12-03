#include "bone_golem.h"

BoneGolem::BoneGolem(int player) : Minion{"Bone Golem", "Gain +1/+1 whenever a minion leaves play", 2, player, 1, 3, 1, 0} {};

BoneGolem::~BoneGolem() {};

void BoneGolem::notifyCardMinionLeave(Board &brd, Card &target) {
  atck++;
  def++;
};
