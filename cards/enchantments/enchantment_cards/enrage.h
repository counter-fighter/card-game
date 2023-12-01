#include "enchantment.h"

class Enrage : public Enchantment {
    Enrage(int player);
    virtual ~Enrage();

    void attach(Minion &target) override;
};