#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>
#include <memory>
#include "card.h"

using namespace std;

class Player {
    int id, magic, health;
    string name;
    vector<string> deck;
    vector<unique_ptr<Card>> hand;
    vector<unique_ptr<Card>> deck;
    // should graveyard and spells removed also be here? Or on board instead?

    public:
        Player(int id, string name, istringstream &iss); // magic is initialized to 0 and hand is initially empty.
        ~Player();
        void startTurn();
        void endTurn();
        void drawCard();
        void playCard();
        void setMagic(const int n);
        int getMagic() const;
        int getID() const;
        void setName(const string name);
        void setDeck(const vector<string> deck);
        vector<unique_ptr<Card>> getHand() const;
};

#endif
