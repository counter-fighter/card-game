#include "enchantment.h"

class Silence : public Enchantment {
    Silence();
    virtual ~Silence();

    void attach(Minion *target) override;
};