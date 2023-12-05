#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "minion.h"

class Enchantment : public Card {
    protected:
        string atck, def;
        const CardType ct = CardType::Enchantment;
        const TargetType tt = TargetType::MinionTarget;

    public :
        Enchantment(string name, string desc, int cost, int player, string atck = "", string def = "");
        virtual ~Enchantment();
        virtual void attach(Minion &target) = 0;
        virtual void detach(Minion &target) = 0;
        CardType getCardType() const override; 
        TargetType getTargetType() const override; 
        string getAttack() const;
        string getDefence() const;
};



#endif
