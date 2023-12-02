#include "minion.h"

class FireElemental : public Minion {
  public :
    FireElemental(int player);
    ~FireElemental();
    void notifyCardMinionLeave(Board &brd, Card &target) override;
};