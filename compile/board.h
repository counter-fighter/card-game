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

  public:
    Board();
    ~Board();
    void initPlayer(int playerID, string pName, string deckfile); // initializes a player

    // plays a card from hand, discards spell after use or places minion/ritual/enchanment on board
    void playACard(int cardInd, int playerID, int targetPlayer = -1, int targetCard = -1); 

    void checkCardStates(); // checks all card states and moves a card to different area if conditions are met

    // Notify all cards on board
    void notifyTurnStart(); // notifies turn start for all minions/rituals on board
    void notifyTurnEnd(); // notifies turn end for all minions/rituals on board
    void notifyMinionEnter(int playerID); // notifies all minions/rituals that a minion entered the board
    void notifyMinionLeave(int playerID, Card &target); // notifies all minions/rituals that a minion left the board

    // For Printing
    Player getPlayer(int playerID); // returns a player object
    vector<vector<Minion&>> getMinions(); // returns p1's minions in vector[0] and p2's minions in vector[1]
    vector<vector<Ritual&>> getRituals(); // returns p1's ritual in vector[0][0] and p2's ritual in vector[1][0] (if they exist)
    vector<Minion&> getGraveyard(int playerID); // do we need this?

    // Commands called from main using input
    void startCommand(int playerID);
    void endCommand(); // ends the turn, notifies all cards of Turn End
    void attackCommand(int minionInd, int playerID, int enemyMinion = -1); // performs an attack on an enemy minion or player
    void useMinionAbilityCommand(int minion, int playerID, int targetPlayer = -1, int targetCard = -1); // uses a minion ability

    // Functions that get called from Card Effects/Abilities that affect the board or things on the board
    void summon(string card, int n, int playerID); // summons a minion to the board
    void attach(unique_ptr<Card> card, int playerID, int targetCard); // attaches an enchantment to a minion
    void detach(int playerID, int targetCard); // detaches an enchantment to a minion
    void raiseDead(int playerID); // moves the top card from graveyard to the board (if it exists)
    void removeRitual(int playerTarget); // discards the player's ritual on the board
    void increaseRitualCharges(int playerID, int amount); // increase the number of charges left on ritual
    void addMagic(int playerID, int magic); // increases the player's magic
    void rechargeRitual(int playerID, int charges); // increases the ritual's charges of the player
    void damageAll(int n); // damages all minions on board
    void healAll(int n); // adds Defence to all minions on board
};

#endif
