#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include <memory>
#include "player.h"
#include "card.h"

using namespace std;

class Board {
  vector<vector<unique_ptr<Card>>> board;
  vector<unique_ptr<Player>> players;
  // other fields (deck, graveyard, removedFromPlay?)

  public:
    Board();
    ~Board();
    void damageAll(int n);
    void healAll(int n);
    void playACard(unique_ptr<Card> card);
    void summon(unique_ptr<Card> card, int n);
    void attach(unique_ptr<Card> card);
    void detach(unique_ptr<Card> card);
    void notifyTurnStart();
    void notifyTurnEnd();
    void notifyMinionEnter();
    void notifyMinionLeave();
    Player getPlayer(int playerID);
    vector<vector<Card&>> getBoard();
    vector<unique_ptr<Card&>> getGraveyard(int playerID);
};

#endif
