#include "enchantment.h"

class GiantStrength : public Enchantment {
        void attach(Minion &target) override;
        void detach(Minion &target) override;
    
    public :
        GiantStrength(int player);
        virtual ~GiantStrength();
};