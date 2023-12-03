#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
// #include "player.h"
// #include "card.h"
#include "board.h"
#include "printer.h"

using namespace std;

int main (int argc, char *argv []) {
    const string initArg = "-init", testingArg = "-testing", graphicsArg = "-graphics";
    const string deck1Arg = "-deck1", deck2Arg = "-deck2";
    string initFile, cmd, cardName, deckfile1, deckfile2;
    bool testing = false, graphics = false;
    int currentPlayerID = 0;
    bool fileInput = false, gameOn = true;
    vector<string> validCards {};



    for (int i = 0; i < argc; i++) {
        string arg = argv[i];
        if (arg == initArg && argc > i + 1) { // -init arg
            initFile = argv[i + 1];
            fileInput = true;
        } else if (arg == deck1Arg && argc > i + 1) { // -deck1 arg
            deckfile1 = argv[i + 1];
        } else if (arg == deck2Arg && argc > i + 1) { // -deck2 arg
            deckfile2 = argv[i + 1];
        } else if (arg == testingArg) { // -testing arg
            testing = true;
        } else if (arg == graphicsArg) { // -graphics arg
            graphics = true;
        }
    }

    Printer printer{};
    Board board;
    
    ifstream init{initFile};
    
    int i = 0;
    string line, p1Name, p2Name;

    // game loop from initFile
    while (gameOn) {
        if (fileInput) {
            if (!getline(init, line)) {
                fileInput = false;
                getline(cin, line);
            }
        } else {
            getline(cin, line);
        }
        istringstream lineCmd (line);
        lineCmd >> cmd;

        if (i == 0) { 
            p1Name = cmd;
            i++;
            board.initPlayer(p1Name, i, deckfile1, testing);
            continue;
        } else if (i == 1) { 
            p2Name = cmd; 
            i++;            
            board.initPlayer(p2Name, i, deckfile2, testing);
            continue; 
        }


        if (cmd == "help") {
            // print the help menu
            printer.printHelp();

        } else if (cmd == "end") {
            board.endCommand();
            currentPlayerID = (currentPlayerID == 1) ? 2 : 1;
            board.startCommand(currentPlayerID);

        } else if (cmd == "quit") {
            break;
        } else if (cmd == "attack") {
            int ownMinion, enemyMinion;
            lineCmd >> ownMinion;
            if (lineCmd >> enemyMinion) {
                // attack minion
                board.attackCommand(ownMinion, currentPlayerID, enemyMinion);
            } else {
                // attack player
                board.attackCommand(ownMinion, currentPlayerID);
            }

        } else if (cmd == "play") {
            int cardToPlay, targetPlayer, targetCard;
            lineCmd >> cardToPlay;
            if (lineCmd >> targetPlayer >> targetCard) {
                if (targetCard != 'r') targetCard--;
                board.playACard(cardToPlay, currentPlayerID, targetPlayer, targetCard);
            } else {
                board.playACard(cardToPlay, currentPlayerID);
            }

        } else if (cmd == "use") {
            int minion, targetPlayer, targetCard;
            lineCmd >> minion;
            if (lineCmd >> targetPlayer >> targetCard) {
                if (targetCard != 'r') targetCard--;
                board.useMinionAbilityCommand(minion, currentPlayerID, targetPlayer, targetCard);
            } else {
                // do some error checking for incorrect input
                board.useMinionAbilityCommand(minion, currentPlayerID);
            }

        } else if (cmd == "inspect") {
            int minion;
            if (lineCmd >> minion) {
                Minion &inspectMinion = board.getMinions()[currentPlayerID - 1][minion - 1];
                printer.printInspect(inspectMinion);
            } else {
                // print invalid input
            }

        } else if (cmd == "hand") {
            // printer command for hand
            printer.printHand(board.getPlayer(currentPlayerID).getHand());

        } else if (cmd == "board") {
            // printer command for board
            printer.printBoard(board);

        } else {
            cout << "A valid command was not entered, please enter a valid command" << endl;
        }
        cout << cmd << endl; // just echoing commands, remove later
    }

}
