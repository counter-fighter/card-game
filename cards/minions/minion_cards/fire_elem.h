#include "minion.h"

class FireElement : public Minion {
  FireElement(int player);
  ~FireElement();
  void notifyCardMinionLeave(Board &brd, Card &target) override;
};