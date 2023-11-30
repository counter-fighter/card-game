#ifndef __MINION_H__
#define __MINION_H__
#include "card.h"
class Player; // Replace with Player class when ready


class Minion : public Card {
    int atck, def, actCount, actReset, actCost;
    CardType ct = CardType::Minion;

    Minion(string name, string desc, int cost, int atck, int def, int actCount, int actReset,int actCost);
    ~Minion();

    // Would be overrided by concrete minions
    virtual void notifyCardTurnStart() = 0;
    virtual void notifyCardTurnEnd() = 0;
    // Decide on pointer
    virtual void notifyCardMinionEnter() = 0;
    // Decide on pointer
    virtual void notifyCardMinionLeave() = 0;

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
    
    int getAttack();
    void setDefence(int n);
    int getDefence();
    int getActivationCost();
    CardType getCardType(); //Card type already determined

    // Minions dont have a deafault activity, only override with enchantment or if card has default ability.
    virtual void activateAbility() = 0;
    virtual void activateAbility(Minion &target) = 0;

    // I'm thinking play should be handled between player and board
    //virtual void play(Board &board);
};

#endif
