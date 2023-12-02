#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include <memory>
#include "player.h"
#include "minion.h"
#include "ritual.h"

using namespace std;

class Board {
  vector<vector<unique_ptr<Minion>>> minions;
  vector<vector<unique_ptr<Ritual>>> rituals;
  vector<unique_ptr<Player>> players;
  // other fields (deck, graveyard, removedFromPlay?)

  public:
    Board();
    ~Board();
    void damageAll(int n);
    void healAll(int n);
    void playACard(unique_ptr<Card> card, int playerID);
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
};

#endif
