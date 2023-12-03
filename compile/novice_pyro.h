#include "minion.h"

class NovicePyromancer : public Minion {
  public :
    NovicePyromancer(int player);
    ~NovicePyromancer();
    void activateAbility(Board &brd, Minion &target) override;
};