#include "card.h"

Card::Card(string name): name{name} {}

ostream &operator<<(ostream &out, Card c) {
    out << c.name;
    return out;
}