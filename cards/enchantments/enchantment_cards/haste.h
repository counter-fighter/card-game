#include "enchantment.h"

class Haste : public Enchantment {
    Haste(int player);
    virtual ~Haste();

    void attach(Minion &target) override;
};