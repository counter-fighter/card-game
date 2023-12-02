#include "board.h"

Board::Board(): minions{}, rituals{}, players{} {}

Board::~Board() {}

void Board::damageAll(int n) {
    const int p1 = 0, p2 = 1;
    int minionSizeP1 = minions[p1].size(), minionSizeP2 = minions[p2].size();
    for (int i = 0; i < minionSizeP1; i++) {
        minions[p1][i]->setDefence(minions[p1][i]->getDefence() - n);
    }

    for (int i = 0; i < minionSizeP2; i++) {
        minions[p2][i]->setDefence(minions[p2][i]->getDefence() - n);
    }
}

void Board::healAll(int n) {
    const int p1 = 0, p2 = 1;
    int minionSizeP1 = minions[p1].size(), minionSizeP2 = minions[p2].size();
    for (int i = 0; i < minionSizeP1; i++) {
        minions[p1][i]->setDefence(minions[p1][i]->getDefence() + n);
    }

    for (int i = 0; i < minionSizeP2; i++) {
        minions[p2][i]->setDefence(minions[p2][i]->getDefence() + n);
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
    return *players[playerID - 1];
}

vector<vector<Minion&>> Board::getMinions() {
    return minions;
}

vector<vector<Ritual&>> Board::getRituals() {
    return rituals;
}

vector<Card&> Board::getGraveyard(int playerID) {
    return players[playerID - 1]->getGraveyard();
}
