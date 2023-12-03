#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "card.h"
#include "player.h"
#include "minion.h"
#include "ritual.h"

using namespace std;

class Board {
  const int MAX_MINIONS = 5;
  const int MAX_RITUALS = 1;
  const int NUM_PLAYERS = 2;
  vector<vector<unique_ptr<Minion>>> minions;
  vector<vector<unique_ptr<Ritual>>> rituals;
  vector<unique_ptr<Player>> players;
  vector<vector<unique_ptr<Card>>> discardedCards;
  // other fields (deck, graveyard, removedFromPlay?)

  public:
    Board();
    ~Board();
    void initPlayer(int playerID, string pName, string deckfile);
    void damageAll(int n); // damages all minions on board
    void healAll(int n); // adds Defence to all minions on board

    // plays a card from hand, uses discards spell after use or places minion/ritual/enchanment on board
    void playACard(int cardInd, int playerID, int targetPlayer = -1, int targetCard = -1); 

    void summon(string card, int n, int playerID); // summons a minion to the board
    void attach(unique_ptr<Card> card, int playerID, int targetCard);
    void detach(int playerID, int targetCard);
    void notifyTurnStart();
    void notifyTurnEnd();
    void notifyMinionEnter(int playerID);
    void notifyMinionLeave(int playerID, Card &target);
    Player getPlayer(int playerID);
    vector<vector<Minion&>> getMinions();
    vector<vector<Ritual&>> getRituals();
    vector<Minion&> getGraveyard(int playerID); // do we need this?
    void endCommand();
    void attackCommand(int minionInd, int playerID, int enemyMinion = -1);
    void useMinionAbilityCommand(int minion, int playerID, int targetPlayer = -1, int targetCard = -1);
    void increaseRitualCharges(int playerID, int amount);
    void raiseDead(int playerID);
    void removeRitual(int playerTarget);
    void checkCardStates();
    void addMagic(int playerID, int magic);
    void rechargeRitual(int playerID, int charges);
};

#endif
