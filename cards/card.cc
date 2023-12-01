#include "card.h"

Card::Card(string name, string desc, int cost, int player): name{name}, desc{desc}, cost{cost}, player{player} {}
Card::~Card() {}; // No heap alloc

void Card::notifyCardTurnStart(Board &brd) {};
void Card::notifyCardTurnEnd(Board &brd) {};
void Card::notifyCardMinionEnter(Board &brd, Card &target) {};
void Card::notifyCardMinionLeave(Board &brd, Card &target) {};

int Card::getCost() {return cost;};
int Card::getPlayer() {return player;};
string Card::getName() {return name;};
string Card::getDesc() {return desc;};

// most likely printing by pointer
// Decide on pointer
ostream &operator<<(ostream &out, Card &c) {
    out << c.name;
    return out;
}
