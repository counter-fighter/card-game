#include "card.h"

Card::Card(string name, string desc, int cost, int player): name{name}, desc{desc}, cost{cost}, player{player} {}
Card::~Card() {}; // No heap alloc

void Card::notifyCardTurnStart(Board &brd) {};
void Card::notifyCardTurnEnd(Board &brd) {};
void Card::notifyCardMinionEnter(Board &brd, Card &target) {};
void Card::notifyCardMinionLeave(Board &brd, Card &target) {};

int Card::getCost() const {return cost;};
int Card::getPlayer() const {return player;};
string Card::getName() const {return name;};
string Card::getDesc() const {return desc;};

bool Card::getReturnToHand() { return returnToHand; };
void Card::setReturnToHand(bool tf) { returnToHand = tf; };


// most likely printing by pointer
// Decide on pointer
ostream &operator<<(ostream &out, Card &c) {
    out << c.name;
    return out;
}
