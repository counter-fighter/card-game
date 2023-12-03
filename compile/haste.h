#include "enchantment.h"

class Haste : public Enchantment {
        void attach(Minion &target) override;
        void detach(Minion &target) override;
        
    public :    
        Haste(int player);
        virtual ~Haste();
};