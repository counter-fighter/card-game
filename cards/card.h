#ifndef __CARD_H__
#define __CARD_H__
#include <string>
#include "board.h"
class Board;

using namespace std;

enum class CardType { Minion, Spell, Ritual, Enchantment };

class Card {
    string name, desc;
    int cost;

    public:
        Card(string name, string desc, int cost);
        ~Card();
        virtual CardType getCardType() = 0;
        virtual void notifyCardTurnStart();
        virtual void notifyCardTurnEnd();
        virtual void notifyCardMinionEnter();
        virtual void notifyCardMinionLeave();
        virtual void play(Board *board) = 0;
        virtual void play(Board *board, Card *target) = 0;
        int getCost();

        friend ostream &operator<<(ostream &out, Card &c);
};

#endif
