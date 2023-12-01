#include "minion.h"

class FireElement : public Minion {
  FireElement();
  ~FireElement();
  void notifyCardMinionLeave(Board &brd, Card &target) override;
};