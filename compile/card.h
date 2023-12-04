#ifndef __CARD_H__
#define __CARD_H__
#include <string>
// #include "board.h"
class Board;

using namespace std;

enum class CardType { Minion, Spell, Ritual, Enchantment };
enum class TargetType { NoTarget, MinionTarget, RitualTarget, AllTarget };

class Card {
    protected: 
        string name, desc;
        int cost, player;
        bool returnToHand = false;

    public:
        Card(string name, string desc, int cost, int player);
        virtual ~Card() = 0; // Not virtual
        virtual CardType getCardType() const = 0;
        virtual TargetType getTargetType() const = 0;
        virtual void notifyCardTurnStart(Board &brd);
        virtual void notifyCardTurnEnd(Board &brd);
        virtual void notifyCardMinionEnter(Board &brd, Card &target);
        virtual void notifyCardMinionLeave(Board &brd, Card &target);

        int getCost() const;
        int getPlayer() const;
        string getName() const;
        string getDesc() const;
        bool getReturnToHand();
        void setReturnToHand(bool tf);


        friend ostream &operator<<(ostream &out, Card &c);
};

#endif
