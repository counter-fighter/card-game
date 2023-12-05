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
        bool returnToHand = false; // Returns to hand when true

    public:
        Card(string name, string desc, int cost, int player);
        virtual ~Card() = 0;

        // Pure virtual methods to be ovrrided by all Cards
        // Actual value returned are fields in the specific card types
        virtual CardType getCardType() const = 0;
        virtual TargetType getTargetType() const = 0;

        // Notify functions to override when needed
        virtual void notifyCardTurnStart(Board &brd);
        virtual void notifyCardTurnEnd(Board &brd);
        virtual void notifyCardMinionEnter(Board &brd, Card &target);
        virtual void notifyCardMinionLeave(Board &brd, Card &target);

        // Basic getter methods
        int getCost() const;
        int getPlayer() const;
        string getName() const;
        string getDesc() const;

        // Getter/setter for Return to Hand
        bool getReturnToHand() const;
        void setReturnToHand(bool tf);
};

#endif
