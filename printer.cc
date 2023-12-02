#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer() {}

Printer::~Printer() {}

void Printer::printBoard(const Board& board) {

}

void Printer::printHand(const vector<Card&> hand) {
    
}

void Printer::printInspect(Minion& minion) {
    emplaceBackCard(minion);
    printCards();
    vector<Enchantment&> enchantments = minion.getEnchantments();
    for (Enchantment& i:enchantments) {
        emplaceBackCard(i);
    }
    printCards();
}

void Printer::printCards() {
    int cardsPrinted = 0;
    while (cardsPrinted < cards.size()) { // Prints 5 cards per row.
        for (int line = 0; line < cardHeight; line++) {
            for (int i = cardsPrinted; 
                 i < cardsPrinted + maxCardPerRow && i < cards.size(); i++) {
                cout << cards[i][line];
            }
            cout << endl;
        } 
        cardsPrinted += maxCardPerRow;
    }
    cards.clear();
}

void Printer::emplaceBackCard(Card& card) {
    if (card.getCardType() == CardType::Minion) minionToCardTemplateT(static_cast<Minion&>(card));
    else if (card.getCardType() == CardType::Ritual) ritualToCardTemplateT(static_cast<Ritual&>(card));
    else if (card.getCardType() == CardType::Spell) spellToCardTemplateT(static_cast<Spell&>(card));
    else enchantmentToCardTemplateT(static_cast<Enchantment&>(card));
    cards.emplace_back(card);
}

void Printer::minionToCardTemplateT(const Minion& minion) {
    if (minion.getDesc() == "") { // Minion with no ability.
        card = display_minion_no_ability(minion.getName(), minion.getCost(), minion.getAttack(), 
                                         minion.getDefence());
    } else if (minion.getActivationCost() == 0) { // Minion with triggered ability.
        card = display_minion_triggered_ability(minion.getName(), minion.getCost(), 
                                                minion.getAttack(), minion.getDefence(), 
                                                minion.getDesc());
    } else { // Minion with activated ability.
        card = display_minion_activated_ability(minion.getName(), minion.getCost(), 
                                                minion.getAttack(), minion.getDefence(), 
                                                minion.getActivationCost(), minion.getDesc());
    }
}

void Printer::ritualToCardTemplateT(const Ritual& ritual) {
    card = display_ritual(ritual.getName(), ritual.getCost(), ritual.getActCost(), ritual.getDesc(),
                               ritual.getCharges());
}

void Printer::spellToCardTemplateT(const Spell& spell) {
    card = display_spell(spell.getName(), spell.getCost(), spell.getDesc());
}

void Printer::enchantmentToCardTemplateT(const Enchantment& enchantment) {
    if (enchantment.getDesc() == "") { // Enchantment modifying attack/defense.
        card = display_enchantment_attack_defence(enchantment.getName(), enchantment.getCost(),
                                                  enchantment.getDesc(), enchantment.getAttack(),
                                                  enchantment.getDefense());
    } else { // Enchantment modifying ability.
        card = display_enchantment(enchantment.getName(), enchantment.getCost(), 
                                   enchantment.getDesc());
    }
}
