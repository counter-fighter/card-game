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
        virtual ~Card(); // Not virtual
        virtual CardType getCardType() = 0;
        virtual void notifyCardTurnStart() = 0;
        virtual void notifyCardTurnEnd() = 0;
        // Decide on pointer
        virtual void notifyCardMinionEnter() = 0;
        // Decide on pointer
        virtual void notifyCardMinionLeave() = 0;

        // Play should be handled by Board
        //virtual void play(Board &board) = 0;
        //virtual void play(Board &board, Card &target) = 0;
        int getCost();
        int getPlayer();
        string getName();
        string getDesc();

        friend ostream &operator<<(ostream &out, Card &c);
};

#endif
