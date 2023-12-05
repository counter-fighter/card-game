#ifndef __HASTE_H__
#define __HASTE_H__
#include "enchantment.h"

class Haste : public Enchantment {
        void attach(Minion &target) override;
        void detach(Minion &target) override;
        
    public :    
        Haste(int player);
        virtual ~Haste();
};

#endif