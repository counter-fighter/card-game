#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>

#include "giant_strg.h"
#include "enrage.h"
#include "haste.h"
#include "magic_fat.h"
#include "silence.h"
#include "air_elem.h"
#include "earth_elem.h"
#include "bone_golem.h"
#include "fire_elem.h"
#include "potion_seller.h"
#include "novice_pyro.h"
#include "appren_sum.h"
#include "master_sum.h"
#include "dark_ritual.h"
#include "aura_of_power.h"
#include "standstill.h"
#include "banish.h"
#include "unsummon.h"
#include "recharge.h"
#include "disenchant.h"
#include "raise_dead.h"
#include "blizzard.h"

using namespace std;

const int MAGIC_RESET = 3;
const int HEALTH_RESET = 20;
const int MAX_HAND = 5;

class Player {
    string name;
    int id, magic, health;
    bool testing;
    vector<unique_ptr<Card>> deck;
    vector<unique_ptr<Card>> hand;
    vector<unique_ptr<Minion>> graveyard;
    // should graveyard and spells removed also be here? Or on board instead?
    template<typename T> void moveVec (vector<T> &source, vector<T> &dest);

    public:
        Player(string name, int id, string filename, bool shuffle); // magic is initialized to 0 and hand is initially empty.
        ~Player();
        Player(Player&& p);
        Player(Player& p);

        unique_ptr<Card> allocCard(string name, int id);
        vector<reference_wrapper<Card>> getGraveyard();

        int getPlayerId() const;
        string getPlayerName() const;
        int getPlayerHealth() const;
        int getPlayerMagic() const;
        void setPlayerMagic(int n);
        int getHandSize() const;
        void setPlayerHealth(int n);
        bool getTesting() const;
        bool drawCard();
        
        unique_ptr<Card> playFromHand (int index);
        void sendToGraveyard(unique_ptr<Minion> m);
        unique_ptr<Minion> returnTopFromGraveyard();
        void returnToHand(unique_ptr<Card> c);
        vector<reference_wrapper<Card>> getHand ();
        void discard(int i);
};

#endif
