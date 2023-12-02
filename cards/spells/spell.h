#ifndef __MASTERSUMMONER_H__
#define __MASTERSUMMONER_H__
#include "card.h"
#include "minion.h"

class Spell : public Card {
    const CardType ct = CardType::Spell;
    const TargetType tt;

    public:
        Spell(string name, string desc, int cost, int player, TargetType tt);
        virtual ~Spell();
        virtual bool useSpell(Board &brd, Card &target) = 0;
        CardType getCardType() override;
        TargetType getTargetType() override; 

};


#endif


