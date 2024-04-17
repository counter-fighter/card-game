#include "enchantment.h"

class MagicFatigue : public Enchantment {
        void attach(Minion &target) override;
        void detach(Minion &target) override;

    public :    
        MagicFatigue(int player);
        virtual ~MagicFatigue();
};