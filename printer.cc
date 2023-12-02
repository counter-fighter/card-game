#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer(bool enableGraphics): enableGraphics{enableGraphics} {}

Printer::~Printer() {}

void Printer::printHelp() {
    cout << "Commands: help -- Display this message." << endl;
    cout << "          end -- End the current player\'s turn." << endl;
    cout << "          quit -- End the game." << endl;
    cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
    cout << "          attack minion -- Orders minion to attack the opponent." << endl;
    cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card"
         << " owned by target-player." << endl;
    cout << "          use minion [target-player target-card] -- Use minion\'s special ability, optionally"
         << " targeting target-card owned by target-player." << endl;
    cout << "          inspect minion -- View a minion\'s card and all enchantments on that minion." << endl;
    cout << "          hand -- Describe all cards in your hand." << endl;
    cout << "          board -- Describe all cards on the board." << endl;
}

void Printer::printBoard(const Board& board) {
    vector<vector<Minion&>> minions = board.getMinions();
    vector<vector<Ritual&>> rituals = board.getRituals();
    vector<Player> players{board.getPlayer(1), board.getPlayer(2)};
    vector<vector<Minion&>> graveyards{players[0].getGraveyard(), players[1].getGraveyard()};

    printUpperBoarder();
    printOuterRow(rituals[0], players[0], graveyards[0]);
    printInnerRow(minions[0]);
    printCentreGraphic();
    printInnerRow(minions[1]);
    printOuterRow(rituals[1], players[1], graveyards[1]);
    printLowerBoarder();
}

void Printer::printHand(vector<Card&> hand) {
    for (Card& card:hand) emplaceBackCard(card);
    printCards();
}

void Printer::printInspect(Minion& minion) {
    emplaceBackCard(minion);
    printCards();
    vector<Enchantment&> enchantments = minion.getEnchantment();
    for (Enchantment& echantment:enchantments) emplaceBackCard(echantment);
    printCards();
}
