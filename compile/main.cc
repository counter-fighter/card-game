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
    int currentPlayerID = 1;
    bool fileInput = false, gameOn = true;


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
        } else if (i == 2) {
            board.startCommand(currentPlayerID);
            i++;
        }

        int enemyPlayerID = (currentPlayerID == 1) ? 2 : 1;

        if (cmd == "help") {
            // print the help menu
            printer.printHelp();

        } else if (cmd == "end") {
            board.endCommand();
            currentPlayerID = (currentPlayerID == 1) ? 2 : 1;
            // printer.printStartTurn("");
            cout << "Player " << currentPlayerID << "'s Turn" << endl;
            board.startCommand(currentPlayerID);

        } else if (cmd == "quit") {
            break;
        } else if (cmd == "attack") {
            int ownMinion, enemyMinion;
            if (lineCmd >> ownMinion) {
                if (ownMinion < 1 || ownMinion > static_cast<int> (board.getMinions()[currentPlayerID - 1].size())) {
                    // print error message
                    cout << "Invalid minion to attack with" << endl;
                    continue;
                }
                ownMinion--;
                if (lineCmd >> enemyMinion) {
                    // attack minion
                    if (enemyMinion > static_cast<int> (board.getMinions()[enemyPlayerID - 1].size()) || enemyMinion < 1) {
                        //print error message
                        cout << "Invalid attack target" << endl;
                        continue;
                    }
                    board.attackCommand(ownMinion, currentPlayerID, enemyMinion--);
                } else {
                    // attack player
                    board.attackCommand(ownMinion, currentPlayerID);
                }
            } else {
                // printer.printError("");
                cout << "Invalid number of arguments for attack" << endl;
                continue;
            }

        } else if (cmd == "play") {
            int cardToPlay, targetPlayer = INT32_MIN, targetCard;
            if (lineCmd >> cardToPlay) {
                cardToPlay--;
                if (cardToPlay < 0 || cardToPlay >= board.getPlayer(currentPlayerID).getHandSize()) {
                    // printer.printError("");
                    cout << "Card index " << cardToPlay + 1 << " does not exist in hand" << endl;
                    continue;
                }

                if (lineCmd >> targetPlayer >> targetCard) {
                    if (targetPlayer <= 0 || targetPlayer > NUM_PLAYERS) {
                        // printer.printError("");
                        cout << "Target player " << targetPlayer << " not valid" << endl;;
                        continue;
                    }

                    if (targetCard != 'r' && targetCard <= 0 && 
                        targetCard > static_cast<int>(board.getMinions()[targetPlayer - 1].size())) {
                        // printer.printError("");
                        cout << "Target minion is not in range" << endl;
                        continue;
                    }

                    if (targetCard != 'r') targetCard--;
                    board.playACard(cardToPlay, currentPlayerID, targetPlayer, targetCard);
                } else {
                    if (targetPlayer != INT32_MIN) {
                        // printer.printError("");
                        cout << "Invalid number of arguments for play" << endl;
                        continue;
                    }
                    board.playACard(cardToPlay, currentPlayerID);
                }
            } else {
                // printer.printError("");
                cout << "Invalid number of arguments for play" << endl;
                continue;
            }
            
        } else if (cmd == "use") {
            int minion, targetPlayer = INT32_MIN, targetCard;
            if (lineCmd >> minion) {
                minion--;
                if (minion < 0 || minion >= static_cast<int>(board.getMinions()[currentPlayerID - 1].size())) {
                    // printer.printError("");
                    cout << "Minion index " << minion + 1 << " does not exist on your board" << endl;
                    continue;
                }

                if (lineCmd >> targetPlayer >> targetCard) {
                    if (targetPlayer <= 0 || targetPlayer > NUM_PLAYERS) {
                        // printer.printError("");
                        cout << "Target player " << targetPlayer << " not valid" << endl;;
                        continue;
                    }

                    if (targetCard != 'r' && targetCard <= 0 && 
                        targetCard > static_cast<int>(board.getMinions()[targetPlayer - 1].size())) {
                        // printer.printError("");
                        cout << "Target minion is not in range" << endl;
                        continue;
                    }


                    if (targetCard != 'r') targetCard--;
                    board.useMinionAbilityCommand(minion, currentPlayerID, targetPlayer, targetCard);
                } else {
                    if (targetPlayer != INT32_MIN) {
                        // printer.printError("");
                        cout << "Invalid number of arguments for use" << endl;
                        continue;
                    }
                    board.useMinionAbilityCommand(minion, currentPlayerID);
                }

            } else {
                // printer.printError("");
                cout << "Invalid number of arguments for use" << endl;
                continue;
            }
            

        } else if (cmd == "inspect") {
            int minion;
            if (lineCmd >> minion) {
                if (minion <= 0 || minion > static_cast<int>(board.getMinions()[currentPlayerID - 1].size())) {
                    // printer.printError("");
                    cout << "Minion index " << minion << " does not exist on the board." << endl;
                    continue;
                }
                Minion &inspectMinion = board.getMinions()[currentPlayerID - 1][minion - 1];
                printer.printInspect(inspectMinion);
            } else {
                // printer.printError("");
                cout << "Invalid number of arguments for inspect" << endl;
                continue;
            }

        } else if (cmd == "hand") {
            // printer command for hand
            printer.printHand(board.getPlayer(currentPlayerID).getHand());

        } else if (cmd == "board") {
            // printer command for board
            printer.printBoard(board);

        } else if (cmd == "draw") {
            if (testing) {
                board.getPlayer(currentPlayerID).drawCard();
            } else {
                // print error message
                cout << "A valid command was not entered, please enter a valid command" << endl;
            }
            
        } else if (cmd == "discard") {
            if (testing) {
                int i;
                if (lineCmd >> i) {
                    board.getPlayer(currentPlayerID).discard(i);
                }
            } else {
                // print error message
                cout << "A valid command was not entered, please enter a valid command" << endl;
            }
        } else {
            cout << "A valid command was not entered, please enter a valid command" << endl;
        }

        
        if (board.getPlayer(enemyPlayerID).getPlayerHealth() <= 0) {
            // print winner
            // printer.printWinner(board.getPlayer(currentPlayerID).getPlayerName(), currentPlayerID)
            cout << "Player " << currentPlayerID << ", " << board.getPlayer(currentPlayerID).getPlayerName() << " has won the game!";
            break;
        } else if (board.getPlayer(currentPlayerID).getPlayerHealth() <= 0) {
            // printer.printWinner(board.getPlayer(currentPlayerID).getPlayerName(), currentPlayerID)
            cout << "Player " << enemyPlayerID << ", " << board.getPlayer(currentPlayerID).getPlayerName() << " has won the game!";
            break;
        }
    }

}
