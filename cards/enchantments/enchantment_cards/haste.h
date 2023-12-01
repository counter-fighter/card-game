#include "enchantment.h"

class Haste : public Enchantment {
    Haste();
    virtual ~Haste();

    void attach(Minion *target) override;
};