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

    // Printing Board helper functions. The board is printed textually if showText is true and graphically 
    //   if enableGraphics and showWindow are true. 
    // Prints cards in the ritual, player, and graveyard slots. 
    void printOuterRow(vector<reference_wrapper<Ritual>> ritual, const Player& player, 
                       vector<reference_wrapper<Card>> graveyard, bool showText = true, 
                       bool showWindow = true);

    // Prints cards in the minion slots.
    void printInnerRow(vector<reference_wrapper<Card>> minions, bool showText = true,
                       bool showWindow = true);

    // Prints upper board boarder.
    void printUpperBoarder(bool showText = true, bool showWindow = true);

    // Prints board centre graphic. 
    void printCentreGraphic(bool showText = true, bool showWindow = true); 

    // Prints lower board boarder.
    void printLowerBoarder(bool showText = true, bool showWindow = true); 

    // Prints a maximum of 5 cards with board boarders at the left and right ends. cards is cleared
    //   after printing.
    void printCardsWithBoarder(bool showText = true, bool showWindow = true);


    // Printing hand and inspecting minion helper function. The cards are printed textually if showText
    //   is true and graphically if enableGraphics and showWindow are true.
    // Prints all cards in cards with a maximum of 5 cards per row. cards is cleared after printing.
    void printCards(bool showText = true, bool showWindow = true);


    // Emplaceing argument converted to type card_template_t to the back of cards.
    // Emplaces card to the back of cards.
    void emplaceBackCard(Card& card);

    // Emplaces player converted to type card_template_t to the back of cards.
    void emplaceBackPlayerCard(const Player& player);

    // Returns minion converted to type card_template_t.
    card_template_t minionToCardTemplateT(const Minion& minion);

    // Returns ritual converted to type card_template_t.
    card_template_t ritualToCardTemplateT(const Ritual& ritual); 

    // Returns spell converted to type card_template_t.
    card_template_t spellToCardTemplateT(const Spell& spell);

    // Returns enchantment converted to type card_template_t.
    card_template_t enchantmentToCardTemplateT(const Enchantment& enchantment);
    
    public:
        Printer(bool enableGraphics, Xwindow &window); // enableGraphics should be false by default.
        ~Printer();

        // Outputs a message describing the commands and their formats.
        void printHelp();

        // Outputs a prompt asking for player name for player playerID.
        void printPlayerNamePrompt(int playerID);

        // Outputs a prompt asking for move from player playerID.
        void printPlayersMovePrompt(int playerID);

        // Outputs error message.
        void printError(string error);

        // Outputs winning message for name and player playerID.
        void printWinner(string name, int playerID);

        // Outputs message indicating player playerID's turn.
        void printStartTurn(int playerID);

        // Outputs board textually.
        void printBoard(const Board& board);

        // Outputs hand textually.
        void printHand(vector<reference_wrapper<Card>> hand);

        // Prints inspected minion textually and graphically if enabledGraphics is true.
        void printInspect(Card& minion);

        // Prints hand in window.
        // Requires: enableGraphics == true
        void updateHand(vector<reference_wrapper<Card>> hand);

        // Prints board in window.
        // Requires: enableGraphics == true
        void updateBoard(const Board& board);
};

#endif