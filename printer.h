#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <vector>
#include "board.h"
// #include "card.h"
// #include "minion.h"
// #include "ritual.h"
// #include "spell.h"
#include "ascii_graphics.h"

using namespace std;

class Printer {
    const int cardHeight = 11;
    const int maxCardPerRow = 5;
    const int boarderWidthNoCorner = 165;
    //bool enableGraphics;
    vector<card_template_t> cards;
    // window pointer

    void printOuterRow(vector<Ritual&> ritual, const Player& player, vector<Minion&> graveyard);
    void printInnerRow(vector<Minion&> minions);
    void printUpperBoarder();
    void printCentreGraphic();
    void printLowerBoarder();
    void Printer::printCardsWithBoarder();
    void printCards();
    void emplaceBackCard(Card& card);
    void emplaceBackPlayerCard(const Player& player);
    card_template_t minionToCardTemplateT(const Minion& minion);
    card_template_t ritualToCardTemplateT(const Ritual& ritual); 
    card_template_t spellToCardTemplateT(const Spell& spell);
    card_template_t enchantmentToCardTemplateT(const Enchantment& enchantment);

    public:
        Printer(); //window pointer
        ~Printer();
        void printHelp();
        void printBoard(const Board& board); //clear window (except hand) if enabled print board
        void printHand(vector<Card&> hand); //constantly displayed, updated when changes r made, 
        void printInspect(Minion& minion); //clear window (except hand) if enabled print inspect
};

#endif