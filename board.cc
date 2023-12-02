#include "board.h"

Board::Board(): board{}, players{} {}

Board::~Board() {}

void Board::damageAll(int n) {
    const int p1 = 0, const p2 = 1, minionSizeP1 = board[p1].size(), minionSizeP2 = board[p2].size();
    for (int i = 0; i < minionSizeP1; i++) {
        board[p1][i].setDefence(board[p1][i].getDefence() - n);
    }

    for (int i = 0l i < minionSizeP2; i++) {
        board[p2][i].setDefence(board[p2][i].getDefence() - n);
    }
}

void Board::healAll(int n) {
    const int p1 = 0, const p2 = 1, minionSizeP1 = board[p1].size(), minionSizeP2 = board[p2].size();
    for (int i = 0; i < minionSizeP1; i++) {
        board[p1][i].setDefence(board[p1][i].getDefence() + n);
    }

    for (int i = 0; i < minionSizeP2; i++) {
        board[p2][i].setDefence(board[p2][i].getDefence() + n);
    }
}

void Board::playACard(unique_ptr<Card> card, int playerID) {

}

void Board::summon(unique_ptr<Card> card, int n) {}

void Board::attach(unique_ptr<Card> card) {}

void Board::detach(unique_ptr<Card> card) {}

void Board::notifyTurnStart() {}

void Board::notifyTurnEnd() {}

void Board::notifyMinionEnter() {}

void Board::notifyMinionLeave() {}

Player Board::getPlayer(int playerID) {
    return players[playerID - 1];
}

vector<vector<Card&>> Board::getMinions() {
    return minions;
}

vector<vector<Card&>> Board::getRituals() {
    return rituals;
}

vector<unique_ptr<Card&>> Board::getGraveyard(int playerID) {
    return players[playerID - 1].getGraveyard();
}
