#ifndef __SPELL_H__
#define __SPELL_H__
#include "card.h"
#include "minion.h"

class Spell : public Card {
    const CardType ct = CardType::Spell;
    const TargetType tt;

    public:
        Spell(string name, string desc, int cost, int player, TargetType tt);
        virtual ~Spell();
        virtual void useSpell(Board &brd, Card &target);
        virtual void useSpell(Board &brd);
        CardType getCardType() const override;
        TargetType getTargetType() const override; 

};


#endif


