#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "player.h"
#include "card.h"
#include <memory>

using namespace std;

int main (int argc, char *argv []) {
    const string initArg = "-init", deck1Arg = "-deck1", deck2Arg = "-deck2";
    string initFile, cmd, cardName, deckfile1, deckfile2;
    vector<unique_ptr<Card>> deck1 {};
    vector<string> validCards {};

    Player player1, player2;

    for (int i = 0; i < argc; i++) {
        string arg = argv[i];
        if (arg == initArg && argc > i + 1) { // -init arg
            initFile = argv[i + 1];
        } else if (arg == deck1Arg && argc > i + 1) { // deck1 arg
            deckfile1 = argv[i + 1];
        } else if (arg == deck2Arg && argc > i + 1) { //deck2 arg
            deckfile2 = argv[i + 1];
        }
    }

    ifstream deckStream1{deckfile1};

    while (getline(deckStream1, cardName)) {
        deck1.emplace_back(make_unique<Card>(cardName));
    }

    for (int i = 0; i < deck1.size(); i++) {
        cout << *deck1[i] << endl;
    }

    ifstream init{initFile};
    
    int i = 0;

    // game loop from initFile
    while (init >> cmd) {
        if (i == 0) { player1.setName(cmd); i++; }
        else if (i == 1) { player2.setName(cmd); i++; }
        

        if (cmd == "help") {

        } else if (cmd == "end") {
            
        } else if (cmd == "play") {

        } // add more cmds

        cout << cmd << endl; // just echoing commands, remove later
    }

    // game loop
    while (cin >> cmd) {
        cout << cmd << endl; // echoing commands, remove later
    }

}
