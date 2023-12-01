#include "enchantment.h"

class GiantStrength : public Enchantment {
    GiantStrength(int player);
    virtual ~GiantStrength();

    void attach(Minion &target) override;
    void detach(Minion &target) override;
};