#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <vector>
#include <memory>
#include "card.h"
#include "minion.h"

using namespace std;

class Printer {
    vector<vector<unique_ptr<Card>>> board;
    vector<unique_ptr<Card>> hand;
    unique_ptr<Minion> minion;
    public:
        Printer();
        void printBoard(vector<vector<unique_ptr<Card>>> board);
        void printHand(vector<unique_ptr<Card>> hand);
        void printInspect(unique_ptr<Minion> minion);
};

#endif