#include "enchantment.h"

class Enrage : public Enchantment {
    Enrage();
    virtual ~Enrage();

    void attach(Minion *target) override;
};