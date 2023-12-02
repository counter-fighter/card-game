#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <vector>
#include "board.h"
#include "card.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "ascii_graphics.h"

using namespace std;

class Printer {
    const int cardHeight = 11;
    const int maxCardPerRow = 5;
    const int boarderWidthNoCorner = 165;
    vector<card_template_t> cards;

    public:
        Printer();
        ~Printer();
        void printBoard(const Board& board);
        void printOuterRow(const vector<Ritual&> ritual, const Player& player, 
                           const vector<Minion&> graveyard);
        void printInnerRow(const vector<Minion&> minions);
        void printUpperBoarder();
        void printCentreGraphic();
        void printLowerBoarder();
        void printHand(const vector<Card&> hand);
        void printInspect(Minion& minion);
        void printCardsWithBoarder();
        void printCards();
        void emplaceBackCard(Card& card);
        void emplaceBackPlayerCard(const Player& player);
        card_template_t minionToCardTemplateT(const Minion& minion);
        card_template_t ritualToCardTemplateT(const Ritual& ritual);
        card_template_t spellToCardTemplateT(const Spell& spell);
        card_template_t enchantmentToCardTemplateT(const Enchantment& enchantment);
};

#endif