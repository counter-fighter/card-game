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
    bool enableGraphics;
    vector<card_template_t> cards;
    // window pointer

    void printOuterRow(vector<Ritual&> ritual, const Player& player, 
                           vector<Minion&> graveyard) {
        if (ritual.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
        else emplaceBackCard(ritual[0]);
        cards.emplace_back(CARD_TEMPLATE_EMPTY);
        emplaceBackPlayerCard(player);
        cards.emplace_back(CARD_TEMPLATE_EMPTY);
        if (graveyard.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
        else emplaceBackCard(graveyard[0]);
        printCardsWithBoarder();
    }

    void printInnerRow(vector<Minion&> minions) {
        int cardEmplaced = 0;
        for (Minion& minion:minions) {
            emplaceBackCard(minion);
            cardEmplaced++;
        }
        for (; cardEmplaced < maxCardPerRow; cardEmplaced++) cards.emplace_back(CARD_TEMPLATE_BORDER);
        printCardsWithBoarder();
    }

    void printUpperBoarder() {
        cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        for (int i = 0; i < boarderWidthNoCorner; i++) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
    }

    void printCentreGraphic() {
        for (string i:CENTRE_GRAPHIC) cout << i << endl;
    }

    void printLowerBoarder() {
        cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
        for (int i = 0; i < boarderWidthNoCorner; i++) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
    }

    void Printer::printCardsWithBoarder() {
        for (int line = 0; line < cardHeight; line++) {
            cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
            for (int i = 0; i < maxCardPerRow; i++) {
                cout << cards[i][line];
            }
            cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
        } 
        cards.clear();
    }

    void printCards() {
        int cardsPrinted = 0;
        while (cardsPrinted < cards.size()) { 
            for (int line = 0; line < cardHeight; line++) {
                for (int i = cardsPrinted; i < cardsPrinted + maxCardPerRow && i < cards.size(); i++) { // Prints MAX 5 cards per row.
                    cout << cards[i][line];
                }
                cout << endl;
            } 
            cardsPrinted += maxCardPerRow;
        }
        cards.clear();
    }

    void emplaceBackCard(Card& card) {
        card_template_t convertedCard;
        if (card.getCardType() == CardType::Minion) {
            convertedCard = minionToCardTemplateT(static_cast<Minion&>(card));
        } else if (card.getCardType() == CardType::Ritual) {
            convertedCard = ritualToCardTemplateT(static_cast<Ritual&>(card));
        } else if (card.getCardType() == CardType::Spell) {
            convertedCard = spellToCardTemplateT(static_cast<Spell&>(card));
        } else {
            convertedCard = enchantmentToCardTemplateT(static_cast<Enchantment&>(card));
        }
        cards.emplace_back(convertedCard);
    }

    void emplaceBackPlayerCard(const Player& player) {
        card_template_t convertedCard;
        convertedCard = display_player_card(player.getPlayerId(), player.getPlayerName(), 
                                            player.getPlayerHealth(), player.getPlayerMagic());
        cards.emplace_back(convertedCard);
    }

    card_template_t minionToCardTemplateT(const Minion& minion) {
        card_template_t convertedCard;
        if (minion.getDesc() == "") {
            convertedCard = display_minion_no_ability(minion.getName(), minion.getCost(), minion.getAttack(), 
                                                    minion.getDefence());
        } else if (minion.getActivationCost() == 0) {
            convertedCard = display_minion_triggered_ability(minion.getName(), minion.getCost(), 
                                                            minion.getAttack(), minion.getDefence(), 
                                                            minion.getDesc());
        } else {
            convertedCard = display_minion_activated_ability(minion.getName(), minion.getCost(), 
                                                            minion.getAttack(), minion.getDefence(), 
                                                            minion.getActivationCost(), minion.getDesc());
        }
        return convertedCard;
    }

    card_template_t ritualToCardTemplateT(const Ritual& ritual) {
        card_template_t convertedCard;
        convertedCard = display_ritual(ritual.getName(), ritual.getCost(), ritual.getActionCost(),
                                    ritual.getDesc(), ritual.getCharges());
        return convertedCard;
    }

    card_template_t spellToCardTemplateT(const Spell& spell) {
        card_template_t convertedCard;
        convertedCard = display_spell(spell.getName(), spell.getCost(), spell.getDesc());
        return convertedCard;
    }

    card_template_t enchantmentToCardTemplateT(const Enchantment& enchantment) {
        card_template_t convertedCard;
        if (enchantment.getDesc() == "") {
            convertedCard = display_enchantment_attack_defence(enchantment.getName(), enchantment.getCost(),
                                                            enchantment.getDesc(), enchantment.getAttack(),
                                                            enchantment.getDefence());
        } else {
            convertedCard = display_enchantment(enchantment.getName(), enchantment.getCost(), 
                                                enchantment.getDesc());
        }
        return convertedCard;
    }   

    public:
        Printer(bool enableGraphics); //window pointer
        ~Printer();
        void printHelp();
        void printBoard(const Board& board); //clear window (except hand) if enabled print board
        void printHand(vector<Card&> hand); //constantly displayed, updated when changes r made, 
        void printInspect(Minion& minion); //clear window (except hand) if enabled print inspect
};

#endif