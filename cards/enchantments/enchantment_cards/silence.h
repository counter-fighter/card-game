#include "enchantment.h"

class Silence : public Enchantment {
    Silence(int player);
    virtual ~Silence();

    void attach(Minion &target) override;
    void detach(Minion &target) override;

};