#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "card.h"
#include "minion.h"

class Enchantment : public Card {
    protected:
        string atck, def;
        CardType ct = CardType::Enchantment;

    public :
        Enchantment(string name, string desc, int cost, int player, string atck = "", string def = "");
        virtual ~Enchantment();
        virtual void attach(Minion &target) = 0;
        virtual void detach(Minion &target) = 0;
        CardType getCardType() override; 
        string getAttack();
        string getDefence();
};



#endif