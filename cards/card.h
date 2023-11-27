#ifndef __CARD_H__
#define __CARD_H__
#include <string>
#include "board.h"

using namespace std;

enum class CardType { Minion, Spell, Ritual, Enchantment };

class Card {
    string name, desc;
    int cost;

    public:
        Card(string name, string desc, int cost);

        virtual CardType getCardType() = 0;
        virtual void notifyCardTurnStart();
        virtual void notifyCardTurnEnd();
        virtual void notifyCardMinionEnter();
        virtual void notifyCardMinionLeave();
        virtual void play(Board *board);
        virtual void play(Board *board, Card *target);
        int getCost();

        friend ostream &operator<<(ostream &out, Card &c);
};

#endif