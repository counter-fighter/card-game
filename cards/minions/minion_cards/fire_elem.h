#include "minion.h"

class FireElemental : public Minion {
  public :
    FireElemental(int player);
    ~FireElemental();
    void notifyCardMinionEnter(Board &brd, Card &target) override;
};