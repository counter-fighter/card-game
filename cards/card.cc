#include "card.h"

Card::Card(string name, string desc, int cost): name{name}, desc{desc}, cost{cost} {}
Card::~Card() {}; // No heap alloc

int Card::getCost() {return cost;};
int Card::getPlayer() {return player;};
string Card::getName() {return name;};
string Card::getDesc() {return desc;};

// most likely printing by pointer
// Decide on pointer
ostream &operator<<(ostream &out, Card c) {
    out << c.name;
    return out;
}
