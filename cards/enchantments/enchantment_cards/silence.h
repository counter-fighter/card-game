#include "enchantment.h"

class Silence : public Enchantment {
        void attach(Minion &target) override;
        void detach(Minion &target) override;

    public :
        Silence(int player);
        virtual ~Silence();
};