#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "player.h"
#include "card.h"
#include <memory>

using namespace std;

int main (int argc, char *argv []) {
    const string initArg = "-init", testingArg = "-testing", graphicsArg = "-graphics";
    const string deck1Arg = "-deck1", deck2Arg = "-deck2";
    string initFile, cmd, cardName, deckfile1, deckfile2;
    bool testing = false, graphics = false;
    // vector<unique_ptr<Card>> deck1 {};
    vector<string> validCards {};

    Board board;
    // Player player1, player2;

    for (int i = 0; i < argc; i++) {
        string arg = argv[i];
        if (arg == initArg && argc > i + 1) { // -init arg
            initFile = argv[i + 1];
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

    ifstream deckStream1{deckfile1}, deckStream2{deckfile2};

    // while (getline(deckStream1, cardName)) {
    //     deck1.emplace_back(make_unique<Card>(cardName));
    // }

    // for (int i = 0; i < deck1.size(); i++) {
    //     cout << *deck1[i] << endl;
    // }

    ifstream init{initFile};
    
    int i = 0;
    string line, p1Name, p2Name;

    // game loop from initFile
    while (getline(init, line)) {
        if (i == 0) { p1Name = cmd; i++; }
        else if (i == 1) { p2Name = cmd; i++; }

        istringstream lineCmd (line);
        lineCmd >> cmd;

        if (cmd == "help") {
            // print the help 
        } else if (cmd == "end") {
            // end 
        } else if (cmd == "quit") {
            break;
        } else if (cmd == "attack") {
            string ownMinion, enemyMinion;
            lineCmd >> ownMinion;
            if (lineCmd >> enemyMinion) {
                // attack minion
            } else {
                // attack player
            }
 
        } else if (cmd == "play") {
            string cardToPlay;
            lineCmd >> cardToPlay;
            

        } else if (cmd == "use") {

        } else if (cmd == "inspect") {

        } else if (cmd == "hand") {

        } else if (cmd == "board") {

        } else {
            cout << "A valid command was not entered, please enter a valid command" << endl;
        }

        cout << cmd << endl; // just echoing commands, remove later
    }

    // game loop
    while (cin >> cmd) {
        cout << cmd << endl; // echoing commands, remove later
    }

}
