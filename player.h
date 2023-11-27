#ifndef __PLAYER_H__
#define __PLAYER_H_
#include <string>_
#include <vector>
#include <memory>

using namespace std;

class Player {
    int id, magic;
    string name;
    vector<unique_ptr<int>> hand;

    public:
        Player(int id, string name); // magic is initialized to 0 and hand is initially empty.
        void startTurn();
        void endTurn();
        void drawCard();
        void playCard();
        void setMagic(const int n);
        int getMagic() const;
        int getID() const;
        vector<unique_ptr<int>> getHand() const;
};

#endif
