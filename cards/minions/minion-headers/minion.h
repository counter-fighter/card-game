#ifndef __MINION_H__
#define __MINION_H__
#include "card.h"
class Player;


class Minion : public Card {
    int attack, defence;

    void attack(Minion &target);
    void attack(Player &target);
    void activateAbility();
    void activateAbility(Minion &target);
    void inspect();
    int getActionCount();
    void setAttack(int n);
    int getAttack();
    void setDefence(int n);
    int getDefence();
    void setActivationCost(int n);
    int getActivationCost();
    virtual void play(Board &board);
    virtual CardType getCardType();
};

#endif
