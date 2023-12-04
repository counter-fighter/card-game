#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <vector>
#include <functional>
#include "board.h"
#include "ascii_graphics.h"
#include "window.h"

using namespace std;

class Printer {
    const int cardHeight = 11;
    const int maxCardPerRow = 5;
    const int boarderWidthNoCorner = 165;
    bool enableGraphics;
    vector<card_template_t> cards;
    Xwindow* window;
    
    void printOuterRow(vector<reference_wrapper<Ritual>> ritual, const Player& player, 
                       vector<reference_wrapper<Minion>> graveyard);
    void printInnerRow(vector<reference_wrapper<Minion>> minions);
    void printUpperBoarder();
    void printCentreGraphic();
    void printLowerBoarder();
    void printCardsWithBoarder();
    void printCards();
    void emplaceBackCard(Card& card);
    void emplaceBackPlayerCard(const Player& player);
    card_template_t minionToCardTemplateT(const Minion& minion);
    card_template_t ritualToCardTemplateT(const Ritual& ritual); 
    card_template_t spellToCardTemplateT(const Spell& spell);
    card_template_t enchantmentToCardTemplateT(const Enchantment& enchantment);

    public:
        Printer(bool enableGraphics, Xwindow &window);
        ~Printer();
        void printHelp();
        void printBoard(const Board& board);
        void printHand(vector<reference_wrapper<Card>> hand); 
        void printInspect(Minion& minion);
        void updateHand(vector<reference_wrapper<Card>> hand); // Requires enableGraphics == true
};

#endif