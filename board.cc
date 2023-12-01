#include "board.h"

Board::Board() {}

Board::~Board() {}

void Board::damageAll(int n) {}

void Board::healAll(int n) {}

void Board::playACard(unique_ptr<Card> card) {}

void Board::summon(unique_ptr<Card> card, int n) {}

void Board::attach(unique_ptr<Card> card) {}

void Board::detach(unique_ptr<Card> card) {}

void Board::notifyTurnStart() {}

void Board::notifyTurnEnd() {}

void Board::notifyMinionEnter() {}

void Board::notifyMinionLeave() {}

Player Board::getPlayer(int playerID) {}

vector<vector<unique_ptr<Card>>> Board::getBoard() {}

vector<unique_ptr<Card>> Board::getGraveyard(int playerID) {}
