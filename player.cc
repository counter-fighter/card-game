#include "player.h"

Player::Player(): name{""} {}

Player::Player(string name, vector<string> deck): name{name}, deck{deck} {}

void Player::setName(string name) {
    this->name = name;
}

void Player::setDeck(vector<string> deck) {
    this->deck = deck;
}
