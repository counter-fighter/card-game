#ifndef __CARD_H__
#define __CARD_H__
#include <string>
#include "board.h"
class Board;

using namespace std;

enum class CardType { Minion, Spell, Ritual, Enchantment };

class Card {
    string name, desc;
    int cost, player;

    public:
        Card(string name, string desc, int cost);
        ~Card(); // Not virtual
        virtual CardType getCardType() = 0;
        virtual void notifyCardTurnStart(Board &brd);
        virtual void notifyCardTurnEnd(Board &brd);
        virtual void notifyCardMinionEnter(Board &brd, Card &target);
        virtual void notifyCardMinionLeave(Board &brd, Card &target);

        int getCost();
        int getPlayer();
        string getName();
        string getDesc();

        friend ostream &operator<<(ostream &out, Card &c);
};

#endif
