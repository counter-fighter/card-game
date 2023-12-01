#include "enchantment.h"

class MagicFatigue : public Enchantment {
    MagicFatigue();
    virtual ~MagicFatigue();

    void attach(Minion *target) override;
};