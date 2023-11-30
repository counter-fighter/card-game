#ifndef __MASTERSUMMONER_H__
#define __MASTERSUMMONER_H__
#include "card.h"

class Spell : public Card {
    public:
        Spell(string name, string desc, int cost, int player);
        virtual ~Spell();
        virtual bool useSpell(Minion* target) const;
        virtual bool useSpell(Ritual* target) const;
        CardType getCardType();
};


#endif


