#include "card.h"

Card::Card(string name, string desc, int cost, int player): name{name}, desc{desc}, cost{cost}, player{player} {}

Card::~Card() {}; // No heap alloc

// Notify functions to be overrided if needed
void Card::notifyCardTurnStart(Board &brd) {};
void Card::notifyCardTurnEnd(Board &brd) {};
void Card::notifyCardMinionEnter(Board &brd, Card &target) {};
void Card::notifyCardMinionLeave(Board &brd, Card &target) {};

// Getter functions for basic information
int Card::getCost() const {return cost;};
int Card::getPlayer() const {return player;};
string Card::getName() const {return name;};
string Card::getDesc() const {return desc;};

// Getter/setter for Return to Hand
bool Card::getReturnToHand() const { return returnToHand; };
void Card::setReturnToHand(bool tf) { returnToHand = tf; };

