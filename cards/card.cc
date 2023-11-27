#include "card.h"

Card::Card(string name, string desc, int cost): name{name}, desc{desc}, cost{cost} {}

ostream &operator<<(ostream &out, Card c) {
    out << c.name;
    return out;
}