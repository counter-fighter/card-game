#include "enchantment.h"

class GiantStrength : public Enchantment {
    GiantStrength();
    virtual ~GiantStrength();

    void attach(Minion *target) override;
};