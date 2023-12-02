#ifndef __MINION_H__
#define __MINION_H__
#include <memory>
#include "enchantment.h"
#include "card.h"
class Player; // Replace with Player class when ready


class Minion : public Card {
    protected :
        int atck, atckReset, def, defReset, actCount, actReset, actCost;
        CardType ct = CardType::Minion;
        vector <unique_ptr<Enchantment>> enchants;



        // I'm thinking play should be handled between player and board
        //virtual void play(Board &board);

        void notifyCardTurnStart(Board &brd) override;

    public :
        Minion(string name, string desc, int cost, int player, int atck, int def, int actReset, int actCost);
        virtual ~Minion();
        
        void attack(Minion &target);
        void attack(Player &target);

        // Should be handled by print, or an override on ostream
        //void inspect();

        int getActionCount();
        int setActionCount(int n);
        
        // We shouldn't have a setter function for attack and actCost, otherwise that just 
        //   breaks the encapsulation. I was thinking of making enchantment
        //   as a friend or some kind of work around to only allow enchantment
        //   to have access to minion.
        // void setAttack(int n);
        // void setActivationCost(int n);
        void attachEnchant (unique_ptr<Enchantment> ench);
        void detachEnchant ();
        void detachAllEnchant ();

        void setAttack(int n);
        void setDefence(int n);
        void setAttackReset(int n);
        void setDefenceReset(int n);
        void setActReset(int n);
        void setActCost(int n);

        int getAttack();
        int getDefence();
        int getAttackReset();
        int getDefenceReset();
        int getDefenceReset();
        int getActivationCost();
        int getActionReset();
        CardType getCardType() override; //Card type already determined

        // Minions dont have a deafault activity, only override with enchantment or if card has default ability.
        virtual void activateAbility(Board &brd);
        virtual void activateAbility(Board &brd, Minion &target);

};

#endif
