#ifndef __ENRAGE_H__
#define __ENRAGE_H__
#include "enchantment.h"

class Enrage : public Enchantment {
        void attach(Minion &target) override;
        void detach(Minion &target) override;
    public :
        Enrage(int player);
        virtual ~Enrage();

};

#endif
