#include <iostream>
#include "printer.h"

using namespace std;

void Printer::printOuterRow(vector<reference_wrapper<Ritual>> ritual, const Player& player, 
                            vector<reference_wrapper<Minion>> graveyard) {
    if (ritual.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
    else emplaceBackCard(ritual[0].get());
    cards.emplace_back(CARD_TEMPLATE_EMPTY);
    emplaceBackPlayerCard(player);
    cards.emplace_back(CARD_TEMPLATE_EMPTY);
    if (graveyard.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
    else emplaceBackCard(graveyard[0].get());
    printCardsWithBoarder();
}

void Printer::printInnerRow(vector<reference_wrapper<Card>> minions) {
    int cardEmplaced = 0;
    for (int i = 0; i < static_cast<int>(minions.size()); i++) {
        emplaceBackCard(minions[i].get());
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

void Printer::Printer::printCardsWithBoarder() {
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
    while (cardsPrinted < static_cast<int>(cards.size())) { 
        for (int line = 0; line < cardHeight; line++) {
            for (int i = cardsPrinted; i < cardsPrinted + maxCardPerRow && i < static_cast<int>(cards.size()); i++) { // Prints MAX 5 cards per row.
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

void Printer::emplaceBackCard(Minion &minion) {
    card_template_t convertedCard = minionToCardTemplateT(std::move(minion));
    cards.emplace_back(convertedCard);
}

void Printer::emplaceBackPlayerCard(const Player& player) {
    card_template_t convertedCard;
    convertedCard = display_player_card(player.getPlayerId(), player.getPlayerName(), 
                                        player.getPlayerHealth(), player.getPlayerMagic());
    cards.emplace_back(convertedCard);
}

card_template_t Printer::minionToCardTemplateT(const Minion& minion) {
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

Printer::Printer() {}

Printer::~Printer() {}

void Printer::printHelp() {
    cout << "Commands: help -- Display this message." << endl;
    cout << "          end -- End the current player\'s turn." << endl;
    cout << "          quit -- End the game." << endl;
    cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
    cout << "          attack minion -- Orders minion to attack the opponent." << endl;
    cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card"
         << " owned by target-player." << endl;
    cout << "          use minion [target-player target-card] -- Use minion\'s special ability, optionally"
         << " targeting target-card owned by target-player." << endl;
    cout << "          inspect minion -- View a minion\'s card and all enchantments on that minion." << endl;
    cout << "          hand -- Describe all cards in your hand." << endl;
    cout << "          board -- Describe all cards on the board." << endl;
}

void Printer::printBoard(const Board& board) {
    vector<vector<reference_wrapper<Card>>> minions = board.getMinions();
    vector<vector<reference_wrapper<Ritual>>> rituals = board.getRituals();
    vector<reference_wrapper<Player>> players{board.getPlayer(1), board.getPlayer(2)};
    vector<vector<reference_wrapper<Minion>>> graveyards {players[0].get().getGraveyard(), players[1].get().getGraveyard()};

    printUpperBoarder();
    printOuterRow(rituals[0], players[0].get(), graveyards[0]);
    printInnerRow(minions[0]);
    printCentreGraphic();
    printInnerRow(minions[1]);
    printOuterRow(rituals[1], players[1].get(), graveyards[1]);
    printLowerBoarder();

    
}

void Printer::printHand(vector<reference_wrapper<Card>> hand) {
    for (reference_wrapper<Card> card:hand) emplaceBackCard(card.get());
    printCards();
}

void Printer::printInspect(Card& minion) {
    emplaceBackCard(minion);
    printCards();
    vector<reference_wrapper<Enchantment>> enchantments = static_cast<Minion&>(minion).getEnchantment();
    for (reference_wrapper<Enchantment> echantment:enchantments) emplaceBackCard(echantment.get());
    printCards();
}
