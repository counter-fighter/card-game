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
    const card_template_t blank;
    card_template_t card;
    vector<card_template_t> cards;

    public:
        Printer();
        ~Printer();
        void printBoard(const Board& board);
        void printHand(const vector<Card&> hand);
        void printInspect(Minion& minion);
        void printCards();
        void emplaceBackCard(Card& card);
        void minionToCardTemplateT(const Minion& minion);
        void ritualToCardTemplateT(const Ritual& ritual);
        void spellToCardTemplateT(const Spell& spell);
        void enchantmentToCardTemplateT(const Enchantment& enchantment);
};

#endif