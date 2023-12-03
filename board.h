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
  vector<vector<unique_ptr<Minion>>> minions;
  vector<vector<unique_ptr<Ritual>>> rituals;
  vector<unique_ptr<Player>> players;
  vector<vector<unique_ptr<Card>>> discardedCards;
  // other fields (deck, graveyard, removedFromPlay?)

  public:
    Board();
    ~Board();
    void initPlayer(int playerID, string pName, string deckfile);
    void damageAll(int n);
    void healAll(int n);
    void playACard(int cardInd, int playerID, int targetPlayer = -1, int targetCard = -1);
    void summon(unique_ptr<Card> card, int n);
    void attach(unique_ptr<Card> card);
    void detach(unique_ptr<Card> card);
    void notifyTurnStart();
    void notifyTurnEnd();
    void notifyMinionEnter();
    void notifyMinionLeave();
    Player getPlayer(int playerID);
    vector<vector<Minion&>> getMinions();
    vector<vector<Ritual&>> getRituals();
    vector<Card&> getGraveyard(int playerID);
    void endCommand();
    void attackCommand(int minionInd, int playerID, int enemyMinion = -1);
    void useMinionAbilityCommand(int minion, int playerID, int targetPlayer = -1, int targetCard = -1);
    void increaseRitualCharges(int playerID, int amount);
    void raiseDead();
    void removeRitual();
};

#endif
