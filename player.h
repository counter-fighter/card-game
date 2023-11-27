#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>

using namespace std;

class Player {
    string name;
    vector<string> deck;

    public:
        Player();
        Player(string name, vector<string> deck);
        void setName(string n); // remove later, once we create players w/ names
        void setDeck(vector<string> deck); // same here

};

#endif
