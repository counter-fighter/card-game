#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "board.h"
#include "printer.h"

using namespace std;

int main (int argc, char *argv []) {
    const string initArg = "-init", testingArg = "-testing", graphicsArg = "-graphics";
    const string deck1Arg = "-deck1", deck2Arg = "-deck2", bonusArg = "-enableBonus";
    string initFile, cmd, cardName, deckfile1, deckfile2;
    bool testing = false, graphics = false;
    const int NAME_LIMIT = 13;
    int currentPlayerID = 1, turn = 1;
    bool fileInput = false, gameOn = true;
    bool enableBonus = false;

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
        } else if (arg == bonusArg) { // bonus arg
            enableBonus = true;
        }
    }

    Xwindow window{graphics};
    Printer printer{graphics, window};
    Board board;
    
    ifstream init{initFile};
    
    int i = 0;
    string line, p1Name, p2Name;

    // game loop from initFile
    while (gameOn) {
        try {
            if (graphics && i > 1) {
                printer.updateHand(board.getPlayer(currentPlayerID).getHand()); // update after every move.
                if (cmd != "inspect") printer.updateBoard(board); // updateBoard unless inspecting minion.
            }

            if (fileInput) { // exhaust file input before cin
                if (!getline(init, line)) {
                    fileInput = false;
                    getline(cin, line);
                }
            } else {
                if (i < 2) printer.printPlayerNamePrompt(i + 1); // throw exception for name over 13 character and reprompt
                else printer.printPlayersMovePrompt(currentPlayerID);
                if (!getline(cin, line)) break;
                if (line.length() > NAME_LIMIT && i < 2) { throw std::logic_error("Exceeded maximum 13 character limit for player name"); }
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

            int enemyPlayerID = (currentPlayerID == 1) ? 2 : 1;

            if (cmd == "help") {
                // print the help menu
                printer.printHelp();

            } else if (cmd == "end") {
                board.endCommand(currentPlayerID);
                currentPlayerID = (currentPlayerID == 1) ? 2 : 1;
                if (turn > 1) board.startCommand(currentPlayerID);
                printer.printStartTurn(currentPlayerID);
                turn++;

            } else if (cmd == "quit") {
                break;
            } else if (cmd == "attack") {
                int ownMinion, enemyMinion;
                if (lineCmd >> ownMinion) {
                    if (ownMinion < 1 || ownMinion > static_cast<int> (board.getMinions()[currentPlayerID - 1].size())) {
                        printer.printError("Invalid minion to attack with");
                        continue;
                    }

                    ownMinion--;
                    
                    if (lineCmd >> enemyMinion) {
                        if (enemyMinion > static_cast<int> (board.getMinions()[enemyPlayerID - 1].size()) || enemyMinion < 1) {
                            printer.printError("Invalid attack target");
                            continue;
                        }
                        
                        enemyMinion--;
                        // attack minion, if success, check state on board
                        if (board.attackCommand(ownMinion, currentPlayerID, enemyMinion)) {
                            board.checkCardStates(currentPlayerID);
                            board.checkCardStates(enemyPlayerID);
                        } else {
                            throw std::logic_error("Attack failed.");
                        }
                        
                    } else {
                        // attack player
                        board.attackCommand(ownMinion, currentPlayerID);
                    }
                } else {
                    printer.printError("Invalid number of arguments for attack");
                    continue;
                }

            } else if (cmd == "play") {
                int cardToPlay, targetPlayer = INT32_MIN, targetCard;
                if (lineCmd >> cardToPlay) {
                    cardToPlay--;
                    if (cardToPlay < 0 || cardToPlay >= board.getPlayer(currentPlayerID).getHandSize()) {
                        printer.printError("Card index " + to_string(cardToPlay + 1) + " does not exist in hand");
                        continue;
                    }

                    if (lineCmd >> targetPlayer >> targetCard) {
                        if (targetPlayer <= 0 || targetPlayer > NUM_PLAYERS) {
                            printer.printError("Target player " + to_string(targetPlayer) + " not valid");
                            continue;
                        }

                        if (targetCard != 'r' && targetCard <= 0 && 
                            targetCard > static_cast<int>(board.getMinions()[targetPlayer - 1].size())) {
                            printer.printError("Target minion is not in range");
                            continue;
                        }

                        if (targetCard != 'r') targetCard--;
                        // play a card, if success, check state on board
                        if (board.playACard(cardToPlay, currentPlayerID, targetPlayer, targetCard)) {
                            board.checkCardStates(currentPlayerID);
                            board.checkCardStates(enemyPlayerID);
                        } else {
                            throw std::logic_error("Playing the card failed.");
                        }

                    } else {
                        if (targetPlayer != INT32_MIN) {
                            printer.printError("Invalid number of arguments for play");
                            continue;
                        }

                        // play a card, if success, check state on board
                        if (board.playACard(cardToPlay, currentPlayerID)) {
                            board.checkCardStates(currentPlayerID);
                            board.checkCardStates(enemyPlayerID);
                        } else {
                            throw std::logic_error("Playing the card failed.");
                        }
                    }
                } else {
                    printer.printError("Invalid number of arguments for play");
                    continue;
                }
                
            } else if (cmd == "use") {
                int minion, targetPlayer = INT32_MIN, targetCard;
                if (lineCmd >> minion) {
                    minion--;
                    if (minion < 0 || minion >= static_cast<int>(board.getMinions()[currentPlayerID - 1].size())) {
                        printer.printError("Minion index " + to_string(minion + 1) + " does not exist on your board");
                        continue;
                    }

                    if (lineCmd >> targetPlayer >> targetCard) {
                        if (targetPlayer <= 0 || targetPlayer > NUM_PLAYERS) {
                            printer.printError("Target player " + to_string(targetPlayer) + " not valid");
                            continue;
                        }

                        if (targetCard != 'r' && targetCard <= 0 && 
                            targetCard > static_cast<int>(board.getMinions()[targetPlayer - 1].size())) {
                            printer.printError("Target minion is not in range");
                            continue;
                        }


                        if (targetCard != 'r') targetCard--;
                        // use ability, if success, check state on board
                        if (board.useMinionAbilityCommand(minion, currentPlayerID, targetPlayer, targetCard)) {
                            board.checkCardStates(currentPlayerID);
                            board.checkCardStates(enemyPlayerID);
                        } else {
                            throw std::logic_error("Using minion ability failed.");
                        }
                    } else {
                        if (targetPlayer != INT32_MIN) {
                            printer.printError("Invalid number of arguments for use");
                            continue;
                        }

                        // use ability, if success, check state on board
                        if (board.useMinionAbilityCommand(minion, currentPlayerID)) {
                            board.checkCardStates(currentPlayerID);
                            board.checkCardStates(enemyPlayerID);
                        } else {
                            throw std::logic_error("Using minion ability failed.");
                        }
                    }

                } else {
                    printer.printError("Invalid number of arguments for use");
                    continue;
                }
                

            } else if (cmd == "inspect") {
                int minion;
                char enemy;
                if (lineCmd >> minion) {
                    if (enableBonus && lineCmd >> enemy) {
                        if (enemy == 'e') {
                            if (minion <= 0 || minion > static_cast<int>(board.getMinions()[enemyPlayerID - 1].size())) {
                                printer.printError("Minion index " + to_string(minion) + " does not exist on the board.");
                                continue;
                            }
                            Card& inspectMinion = board.getMinions()[enemyPlayerID - 1][minion - 1];
                            printer.printInspect(inspectMinion);
                            continue;
                        }
                    }

                    if (minion <= 0 || minion > static_cast<int>(board.getMinions()[currentPlayerID - 1].size())) {
                        printer.printError("Minion index " + to_string(minion) + " does not exist on the board.");
                        continue;
                    }

                    Card& inspectMinion = board.getMinions()[currentPlayerID - 1][minion - 1];
                    printer.printInspect(inspectMinion);
                } else {
                    printer.printError("Invalid number of arguments for inspect");
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
                    if (!board.getPlayer(currentPlayerID).drawCard()){
                        printer.printError("Tried to draw, but your hand is full.");
                    }
                } else {
                    printer.printError("A valid command was not entered, please enter a valid command");
                }
            
            } else if (cmd == "discard") {
                if (testing) {
                    int i;
                    if (lineCmd >> i) {
                        if (i > 0 && i <= board.getPlayer(currentPlayerID).getHandSize()) {
                            board.getPlayer(currentPlayerID).discard(i--);
                        } else {
                            printer.printError("Tried to discard card at invalid index " + to_string(i));
                        }
                    }
                } else {
                    printer.printError("A valid command was not entered, please enter a valid command");
                }
            } else {
                printer.printError("A valid command was not entered, please enter a valid command");
            }

            // print winner
            if (board.getPlayer(enemyPlayerID).getPlayerHealth() <= 0) {
                printer.printWinner(board.getPlayer(currentPlayerID).getPlayerName(), currentPlayerID);
                break;
            } else if (board.getPlayer(currentPlayerID).getPlayerHealth() <= 0) {
                printer.printWinner(board.getPlayer(enemyPlayerID).getPlayerName(), enemyPlayerID);
                break;
            }
        } catch (std::logic_error& e) {
            printer.printError(e.what());
            continue;
        } catch (...) {
            continue;
        } // try
    } // while

}