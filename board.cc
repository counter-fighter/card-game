#include "board.h"

Board::Board(): minions{}, rituals{}, players{}, discardedCards{} {}

Board::~Board() {}

void Board::initPlayer(int playerID, string pName, string deckfile) {
    players.emplace_back(make_unique<Player>(playerID, pName, deckfile));
}

void Board::damageAll(int n) {
    const int p1 = 0, p2 = 1;
    int minionSizeP1 = minions[p1].size(), minionSizeP2 = minions[p2].size();
    for (int i = 0; i < minionSizeP1; i++) {
        minions[p1][i]->setDefence(minions[p1][i]->getDefence() - n);
    }

    for (int i = 0; i < minionSizeP2; i++) {
        minions[p2][i]->setDefence(minions[p2][i]->getDefence() - n);
    }
}

void Board::healAll(int n) {
    const int p1 = 0, p2 = 1;
    int minionSizeP1 = minions[p1].size(), minionSizeP2 = minions[p2].size();
    for (int i = 0; i < minionSizeP1; i++) {
        minions[p1][i]->setDefence(minions[p1][i]->getDefence() + n);
    }

    for (int i = 0; i < minionSizeP2; i++) {
        minions[p2][i]->setDefence(minions[p2][i]->getDefence() + n);
    }
}

void Board::playACard(int cardInd, int playerID, int targetPlayer, int targetCard) {
    TargetType targetType = TargetType::NoTarget;
    
    if (targetCard != -1) {
        if (targetCard == 'r') {
            targetType = TargetType::RitualTarget;
        } else {
            targetType = TargetType::MinionTarget;
        }
    }

    unique_ptr<Card> cardToPlay = players[playerID]->playFromHand(cardInd);
    

    // use the effect/place it down
    if (cardToPlay->getCardType() == CardType::Minion) {
        if (minions[playerID - 1].size() < 5) {
            minions[playerID - 1].emplace_back(std::move(cardToPlay));
            notifyMinionEnter(playerID);
        } else {
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
            // error message for full minion board
        }
        
    } else if (cardToPlay->getCardType() == CardType::Ritual) {
        if (rituals[playerID - 1].size() > 0) {
            discardedCards[playerID - 1].emplace_back(std::move(rituals[playerID - 1][0]));
        }
        rituals[playerID - 1].emplace_back(std::move(cardToPlay));

    } else if (cardToPlay->getCardType() == CardType::Spell) {
        Card &cardCast = *cardToPlay.get();
        Spell& spellCast = dynamic_cast<Spell&> (cardCast);
        bool castSuccess;

        if (targetType == TargetType::RitualTarget) {
            Card &target = *rituals[playerID - 1][0];
            spellCast.useSpell(*this, target);
        } else if (targetType == TargetType::MinionTarget) {
            Card &target = *minions[playerID - 1][targetCard];
            spellCast.useSpell(*this, target);
        } else {
            spellCast.useSpell(*this);
        }

        discardedCards[playerID - 1].emplace_back(std::move(cardToPlay));

    } else {
        // unique_ptr<Enchantment> enchant {dynamic_cast<Enchantment*>(std::move(cardToPlay))};
        attach(std::move(cardToPlay), playerID, targetCard);
    }
}

void Board::summon(string card, int n, int playerID) {
    for (int i = 0; i < n; i++) {
        if (minions[playerID - 1].size() < MAX_MINIONS) {
            // add minion to vector, either by creating new from string or std::move(card)
            minions[playerID - 1].emplace_back(players[playerID - 1]->allocCard(card, playerID - 1));
            notifyMinionEnter(playerID);
        }
    }
}

void Board::attach(unique_ptr<Card> card, int playerID, int targetCard) {
    unique_ptr<Enchantment> enchant = unique_ptr<Enchantment> (dynamic_cast<Enchantment*>(card.release()));
    // unique_ptr<Enchantment> enchant = make_unique<Enchantment> (dynamic_cast<Enchantment*> (card.get()));
    minions[playerID - 1][targetCard]->attachEnchant(std::move(enchant));
}

void Board::detach(int playerID, int targetCard) {
    minions[playerID - 1][targetCard]->detachEnchant();
}

void Board::notifyTurnStart() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardTurnStart(*this);
        }
        if (rituals[i].size() > 0) {
            rituals[i][0]->notifyCardTurnStart(*this);
        }
    }
}

void Board::notifyTurnEnd() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardTurnEnd(*this);
        }
        if (rituals[i].size() > 0) {
            rituals[i][0]->notifyCardTurnEnd(*this);
        }
    }
}

void Board::notifyMinionEnter(int playerID) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardMinionEnter(*this, *minions[playerID - 1][minions[playerID - 1].size() - 1]);
        }
        if (rituals[i].size() > 0) {
            rituals[i][0]->notifyCardMinionEnter(*this, *minions[playerID - 1][minions[playerID - 1].size() - 1]);
        }
    }
}

void Board::notifyMinionLeave(int playerID, Card &target) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardMinionLeave(*this, target);
        }
        if (rituals[i].size() > 0) {
            rituals[i][0]->notifyCardMinionEnter(*this, target);
        }
    }
}

Player Board::getPlayer(int playerID) {
    return *players[playerID - 1];
}

vector<vector<Minion&>> Board::getMinions() {
    vector<vector<Minion&>> minionsCopy;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minionsCopy[i].emplace_back(*minions[i][j]);
        }
    }
    return minionsCopy;
}

vector<vector<Ritual&>> Board::getRituals() {
    vector<vector<Ritual&>> ritualsCopy;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (rituals[i].size() > 0) {
            ritualsCopy.emplace_back(*rituals[i][0]);
        }
    }
    return ritualsCopy;
}

vector<Minion&> Board::getGraveyard(int playerID) {
    return players[playerID - 1]->getGraveyard();
}

void Board::startCommand() {
    notifyTurnStart();
}

void Board::endCommand() {
    notifyTurnEnd();
}

void Board::attackCommand(int minionInd, int playerID, int enemyMinion) {
    int enemyPlayer = (playerID == 1) ? 2 : 1;
    
    if (enemyMinion != -1) {
        minions[playerID - 1][minionInd]->attack(*minions[enemyPlayer - 1][minionInd]);
    } else {
        minions[playerID - 1][minionInd]->attack(*players[enemyPlayer - 1]);
    }
}

void Board::useMinionAbilityCommand(int minionInd, int playerID, int targetPlayer, int targetCard) {
    if (targetCard == 'r') {
        // minions[playerID - 1][minionInd]->activateAbility(*this, *rituals[targetPlayer - 1][0]);
        // print error message for now because we don't have any cards that do this
    } else if (targetCard == -1) {
        minions[playerID - 1][minionInd]->activateAbility(*this);
    } else {
        minions[playerID - 1][minionInd]->activateAbility(*this, *minions[targetPlayer - 1][targetCard]);
    }
}

void Board::increaseRitualCharges(int playerID, int amount) {
    rituals[playerID - 1][0]->setCharges(rituals[playerID - 1][0]->getCharges() + amount);
}

void Board::raiseDead(int playerID) {
    if (players[playerID - 1]->getGraveyard().size() > 0 && minions[playerID - 1].size() < MAX_MINIONS) {
        unique_ptr<Minion> raisedMinion {players[playerID - 1]->returnTopFromGraveyard()};
        raisedMinion->setDefence(1);
        minions[playerID - 1].emplace_back(std::move(raisedMinion));
    }
}

void Board::removeRitual(int playerTarget) {
    if (rituals[playerTarget].size() > 0) {
        discardedCards[playerTarget - 1].emplace_back(rituals[playerTarget][0]);
    } else {
        // print error message
    }
    
}

void Board::checkCardStates() {
    const int numPlayers = 2;
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            if (minions[i][j]->getReturnToHand()) {
                Card &targetNotify = dynamic_cast<Card&>(*minions[i][j]);
                notifyMinionLeave(i, targetNotify);
                minions[i][j]->detachAllEnchant();
                players[i]->returnToHand(std::move(minions[i][j])); // not sure if I need to cast to Card
            
            } else if (minions[i][j]->getDefence() <= 0) {
                Card &targetNotify = dynamic_cast<Card&> (*minions[i][j]);
                notifyMinionLeave(i, targetNotify);
                minions[i][j]->detachAllEnchant();
                players[i]->sendToGraveyard(std::move(minions[i][j]));
            }
        }

        if (rituals[i].size() > 0) {
            if (rituals[i][0]->getReturnToHand()) {
                players[i]->returnToHand(std::move(rituals[i][0])); // not sure about cast again
            }
        }
    }
}

void Board::addMagic(int playerID, int magic) {
    players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() + magic);
}

void Board::rechargeRitual(int playerID, int charges) {
    if (rituals[playerID - 1].size() > 0) {
        rituals[playerID - 1][0]->setCharges(rituals[playerID - 1][0]->getCharges() + charges);
    } else {
        // print error message
    }
}

