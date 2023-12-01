#ifndef __MINION_H__
#define __MINION_H__
#include <memory>
#include "enchantment.h"
#include "card.h"
class Player; // Replace with Player class when ready


class Minion : public Card {
    protected :
        int atck, def, actCount, actReset, actCost;
        CardType ct = CardType::Minion;
        vector <unique_ptr<Enchantment>> enchants;

        Minion(string name, string desc, int cost, int player, int atck, int def, int actReset, int actCost);


        // I'm thinking play should be handled between player and board
        //virtual void play(Board &board);

        void notifyCardTurnStart(Board &brd) override;

    public :
        virtual ~Minion();
        
        void attack(Minion &target);
        void attack(Player &target);

        // Should be handled by print, or an override on ostream
        //void inspect();

        int getActionCount();
        
        // We shouldn't have a setter function for attack and actCost, otherwise that just 
        //   breaks the encapsulation. I was thinking of making enchantment
        //   as a friend or some kind of work around to only allow enchantment
        //   to have access to minion.
        // void setAttack(int n);
        // void setActivationCost(int n);
        void attachEnchant (unique_ptr<Enchantment> ench);

        int getAttack();
        int getDefence();
        void minusDefence(int n);
        int getActivationCost();
        int getActionReset();
        CardType getCardType(); //Card type already determined

        // Minions dont have a deafault activity, only override with enchantment or if card has default ability.
        virtual void activateAbility(Board &brd);
        virtual void activateAbility(Board &brd, Minion &target);

        friend class Enchantment;
};

#endif
