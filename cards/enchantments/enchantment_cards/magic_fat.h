#include "enchantment.h"

class MagicFatigue : public Enchantment {
    MagicFatigue(int player);
    virtual ~MagicFatigue();

    void attach(Minion &target) override;
};