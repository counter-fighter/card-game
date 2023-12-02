#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer() {}

Printer::~Printer() {}

void Printer::printBoard(const Board& board) {
    vector<vector<Minion&>> minions = board.getMinions();
    vector<vector<Ritual&>> rituals = board.getRituals();
    vector<Player> players{board.getPlayer(1), board.getPlayer(2)};
    vector<vector<Minion&>> graveyards; // NEED GETGRAVEYARD

    printUpperBoarder();
    printOuterRow(rituals[0], players[0], graveyards[0]);
    printInnerRow(minions[0]);
    printCentreGraphic();
    printInnerRow(minions[1]);
    printOuterRow(rituals[1], players[1], graveyards[1]);
    printLowerBoarder();
}

void Printer::printOuterRow(const vector<Ritual&> ritual, const Player& player, const vector<Minion&> graveyard) {
    if (ritual.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
    else emplaceBackCard(ritual[0]);
    cards.emplace_back(CARD_TEMPLATE_EMPTY);
    emplaceBackPlayerCard(player);
    cards.emplace_back(CARD_TEMPLATE_EMPTY);
    if (graveyard.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
    else emplaceBackCard(graveyard[0]);
    printCardsWithBoarder();
}

void Printer::printInnerRow(const vector<Minion&> minions) {
    int cardEmplaced = 0;
    for (Minion& minion:minions) {
        emplaceBackCard(minion);
        cardEmplaced++;
    }
    for (; cardEmplaced < maxCardPerRow; cardEmplaced++) cards.emplace_back(CARD_TEMPLATE_BORDER);
    printCardsWithBoarder();
}

void Printer::printUpperBoarder() {
    cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (int i = 0; i < boarderWidthNoCorner; i++) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
}

void Printer::printCentreGraphic() {
    for (string i:CENTRE_GRAPHIC) cout << i << endl;
}

void Printer::printLowerBoarder() {
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < boarderWidthNoCorner; i++) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

void Printer::printHand(const vector<Card&> hand) {
    for (Card& card:hand) emplaceBackCard(card);
    printCards();
}

void Printer::printInspect(Minion& minion) {
    emplaceBackCard(minion);
    printCards();
    vector<Enchantment&> enchantments = minion.getEnchantments();
    for (Enchantment& echantment:enchantments) emplaceBackCard(echantment);
    printCards();
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

void Printer::printCards() {
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

void Printer::emplaceBackCard(Card& card) {
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

void Printer::emplaceBackPlayerCard(const Player& player) {
    card_template_t convertedCard;
    convertedCard = display_player_card(int player_num, std::string name, int life, int mana); // NEED GET METHODS FROM PLAYER CLASS
    cards.emplace_back(convertedCard);
}

card_template_t Printer::minionToCardTemplateT(const Minion& minion) {
    card_template_t convertedCard;
    if (minion.getDesc() == "") { // Minion with no ability.
        convertedCard = display_minion_no_ability(minion.getName(), minion.getCost(), minion.getAttack(), 
                                                  minion.getDefence());
    } else if (minion.getActivationCost() == 0) { // Minion with triggered ability.
        convertedCard = display_minion_triggered_ability(minion.getName(), minion.getCost(), 
                                                         minion.getAttack(), minion.getDefence(), 
                                                         minion.getDesc());
    } else { // Minion with activated ability.
        convertedCard = display_minion_activated_ability(minion.getName(), minion.getCost(), 
                                                         minion.getAttack(), minion.getDefence(), 
                                                         minion.getActivationCost(), minion.getDesc());
    }
    return convertedCard;
}

card_template_t Printer::ritualToCardTemplateT(const Ritual& ritual) {
    card_template_t convertedCard;
    convertedCard = display_ritual(ritual.getName(), ritual.getCost(), ritual.getActionCost(),
                                   ritual.getDesc(), ritual.getCharges());
    return convertedCard;
}

card_template_t Printer::spellToCardTemplateT(const Spell& spell) {
    card_template_t convertedCard;
    convertedCard = display_spell(spell.getName(), spell.getCost(), spell.getDesc());
    return convertedCard;
}

card_template_t Printer::enchantmentToCardTemplateT(const Enchantment& enchantment) {
    card_template_t convertedCard;
    if (enchantment.getDesc() == "") { // Enchantment modifying attack/defense.
        convertedCard = display_enchantment_attack_defence(enchantment.getName(), enchantment.getCost(),
                                                           enchantment.getDesc(), enchantment.getAttack(),
                                                           enchantment.getDefence());
    } else { // Enchantment modifying ability.
        convertedCard = display_enchantment(enchantment.getName(), enchantment.getCost(), 
                                            enchantment.getDesc());
    }
    return convertedCard;
}
