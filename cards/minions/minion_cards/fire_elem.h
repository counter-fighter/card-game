#include "minion.h"

class FireElement : public Minion {
  public :
    FireElement(int player);
    ~FireElement();
    void notifyCardMinionLeave(Board &brd, Card &target) override;
};