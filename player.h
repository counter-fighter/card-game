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
#include "card.h"

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
    vector<unique_ptr<Card>> deck;
    vector<unique_ptr<Card>> hand;
    vector<unique_ptr<Minion>> graveyard;
    // should graveyard and spells removed also be here? Or on board instead?

    public:
        Player(string name, int id, string filename, bool shuffle); // magic is initialized to 0 and hand is initially empty.
        ~Player();
        // void drawCard();
        // void playCard();
        // void setMagic(const int n);
        // int getMagic() const;
        // int getID() const;
        // void setName(const string name);
        // void setDeck(const vector<string> deck);
        // vector<unique_ptr<Card>> getHand() const;
        vector<Minion&> getGraveyard();
        int getPlayerId();
        string getPlayerName();
        int getPlayerHealth();
        int getPlayerMagic();
        int getHandSize();
        void setPlayerHealth(int n);
        bool drawCard();
        unique_ptr<Card> playFromHand (int index);
        void sendToGraveyard(unique_ptr<Minion> m);
        void returnToHand(unique_ptr<Card> c);
};

#endif
