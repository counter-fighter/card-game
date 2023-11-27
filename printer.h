#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <vector>
#include <memory>
#include "board.h"
#include "card.h"
#include "minion.h"

using namespace std;

class Printer {
    Printer();
        void printBoard(Board);
        void printHand(Card);
        void printInspect(Minion);
};

#endif