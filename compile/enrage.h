#include "enchantment.h"

class Enrage : public Enchantment {
        void attach(Minion &target) override;
        void detach(Minion &target) override;
    public :
        Enrage(int player);
        virtual ~Enrage();

};