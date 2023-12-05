#include <iostream>
#include "printer.h"

using namespace std;

void Printer::printOuterRow(vector<reference_wrapper<Ritual>> ritual, const Player& player, 
                            vector<reference_wrapper<Card>> graveyard, bool showText, bool showWindow) {
    if (ritual.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
    else emplaceBackCard(ritual[0].get());
    cards.emplace_back(CARD_TEMPLATE_EMPTY);
    emplaceBackPlayerCard(player);
    cards.emplace_back(CARD_TEMPLATE_EMPTY);
    if (graveyard.empty()) cards.emplace_back(CARD_TEMPLATE_BORDER);
    else emplaceBackCard(graveyard[0].get());
    printCardsWithBoarder(showText, showWindow);
}

void Printer::printInnerRow(vector<reference_wrapper<Card>> minions, bool showText, bool showWindow) {
    int cardEmplaced = 0;
    for (int i = 0; i < static_cast<int>(minions.size()); i++) {
        emplaceBackCard(minions[i].get());
        cardEmplaced++;
    }
    for (; cardEmplaced < maxCardPerRow; cardEmplaced++) cards.emplace_back(CARD_TEMPLATE_BORDER);
    printCardsWithBoarder(showText, showWindow);
}

void Printer::printUpperBoarder(bool showText, bool showWindow) {
    string upperBoarder = EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (int i = 0; i < boarderWidthNoCorner; i++) upperBoarder += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    upperBoarder += EXTERNAL_BORDER_CHAR_TOP_RIGHT;
    if (showText) cout << upperBoarder << endl;
    if (showWindow && enableGraphics) window->drawString(window->getX(), window->yNextLine(), upperBoarder);
}

void Printer::printCentreGraphic(bool showText, bool showWindow) {
    for (string line:CENTRE_GRAPHIC) {
        if (showText) cout << line << endl;
        if (showWindow && enableGraphics) window->drawString(window->getX(), window->yNextLine(), line);
    }
}

void Printer::printLowerBoarder(bool showText, bool showWindow) {
    string lowerBoarder = EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < boarderWidthNoCorner; i++) lowerBoarder += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    lowerBoarder += EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
    if (showText) cout << lowerBoarder << endl;
    if (showWindow && enableGraphics) window->drawString(window->getX(), window->yNextLine(), lowerBoarder);
}

void Printer::Printer::printCardsWithBoarder(bool showText, bool showWindow) {
    for (int line = 0; line < cardHeight; line++) {
        string cardLine = EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (int i = 0; i < maxCardPerRow; i++) {
            cardLine += cards[i][line];
        }
        cardLine += EXTERNAL_BORDER_CHAR_UP_DOWN;
        if (showText) cout << cardLine << endl;
        if (showWindow && enableGraphics) window->drawString(window->getX(), window->yNextLine(), cardLine);
    } 
    cards.clear();
}

void Printer::printCards(bool showText, bool showWindow) {
    int cardsPrinted = 0;
    while (cardsPrinted < static_cast<int>(cards.size())) { 
        for (int line = 0; line < cardHeight; line++) {
            string cardLine = "";
            for (int i = cardsPrinted; i < cardsPrinted + maxCardPerRow && i < static_cast<int>(cards.size()); i++) {
                cardLine += cards[i][line];
            }
            if (showText) cout << cardLine << endl;
            if (showWindow && enableGraphics) window->drawString(window->getX(), window->yNextLine(), cardLine);
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

Printer::Printer(bool enableGraphics, Xwindow &window) : enableGraphics{enableGraphics}, window{&window} {}

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

void Printer::printPlayerNamePrompt(int playerID) { cout << "Enter Player " << playerID << "'s name (Maximum 13 Characters): "; }

void Printer::printPlayersMovePrompt(int playerID) { cout << "Player " << playerID << "'s move: "; }

void Printer::printError(string error) { cout << error << endl; }

void Printer::printWinner(string name, int playerID) {
    cout << "Player " << playerID << ", " << name << " has won the game!" << endl;
}

void Printer::printStartTurn(int playerID) { cout << "Player " << playerID << "'s Turn" << endl; }

void Printer::printBoard(const Board& board) {
    vector<vector<reference_wrapper<Card>>> minions = board.getMinions();
    vector<vector<reference_wrapper<Ritual>>> rituals = board.getRituals();
    vector<reference_wrapper<Player>> players{board.getPlayer(1), board.getPlayer(2)};
    vector<vector<reference_wrapper<Card>>> graveyards {players[0].get().getGraveyard(), players[1].get().getGraveyard()};
    
    if (enableGraphics) window->clearAreaUnderHand();
    printUpperBoarder(true, false);
    printOuterRow(rituals[0], players[0].get(), graveyards[0], true, false);
    printInnerRow(minions[0], true, false);
    printCentreGraphic(true, false);
    printInnerRow(minions[1], true, false);
    printOuterRow(rituals[1], players[1].get(), graveyards[1], true, false);
    printLowerBoarder(true, false);
}

void Printer::printHand(vector<reference_wrapper<Card>> hand) {
    if (enableGraphics) window->clearAreaUnderHand();
    for (reference_wrapper<Card> card:hand) emplaceBackCard(card.get());
    printCards(true, false);
}

void Printer::printInspect(Card& minion) {
    if (enableGraphics) window->clearAreaUnderHand();
    emplaceBackCard(minion);
    printCards();
    vector<reference_wrapper<Enchantment>> enchantments = static_cast<Minion&>(minion).getEnchantment();
    for (reference_wrapper<Enchantment> echantment:enchantments) emplaceBackCard(echantment.get());
    printCards();
}

void Printer::updateHand(vector<reference_wrapper<Card>> hand) {
    window->clearHandArea();
    window->drawString(window->getX(), window->getY(), "Current Player Hand:");
    for (reference_wrapper<Card> card:hand) emplaceBackCard(card.get());
    printCards(false, true);
}

void Printer::updateBoard(const Board& board) {
    vector<vector<reference_wrapper<Card>>> minions = board.getMinions();
    vector<vector<reference_wrapper<Ritual>>> rituals = board.getRituals();
    vector<reference_wrapper<Player>> players{board.getPlayer(1), board.getPlayer(2)};
    vector<vector<reference_wrapper<Card>>> graveyards {players[0].get().getGraveyard(), players[1].get().getGraveyard()};
    
    if (enableGraphics) window->clearAreaUnderHand();
    printUpperBoarder(false, true);
    printOuterRow(rituals[0], players[0].get(), graveyards[0], false, true);
    printInnerRow(minions[0], false, true);
    printCentreGraphic(false, true);
    printInnerRow(minions[1], false, true);
    printOuterRow(rituals[1], players[1].get(), graveyards[1], false, true);
    printLowerBoarder(false, true);
}
