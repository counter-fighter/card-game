#ifndef __MASTERSUMMONER_H__
#define __MASTERSUMMONER_H__
#include "card.h"
#include "minion.h"

class Spell : public Card {
    CardType ct = CardType::Spell;

    public:
        Spell(string name, string desc, int cost, int player);
        virtual ~Spell();
        virtual bool useSpell(Board &brd, Card &target) = 0;
        CardType getCardType() override;
};


#endif


