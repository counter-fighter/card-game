#include "board.h"

Board::Board(): minions{}, rituals{}, players{}, discardedCards{} {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        vector<unique_ptr<Minion>> m {};
        minions.emplace_back(std::move(m));
        vector<unique_ptr<Ritual>> r {};
        rituals.emplace_back(std::move(r));
        vector<unique_ptr<Card>> disc {};
        discardedCards.emplace_back(std::move(disc));
    }
}

Board::~Board() {}

void Board::initPlayer(string pName, int playerID, string deckfile, bool shuffle) {
    unique_ptr<Player> player = make_unique<Player> (pName, playerID, deckfile, shuffle);
    for (int i = 0; i < MAX_HAND; i++) {
        player->drawCard();
    }
    players.emplace_back(std::move(player));
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

    unique_ptr<Card> cardToPlay = players[playerID - 1]->playFromHand(cardInd);

    if (targetType != cardToPlay->getTargetType()) {
        // print error message wrong args
        cout << "wrong args for card " + cardToPlay->getName() << endl;
        players[playerID - 1]->returnToHand(std::move(cardToPlay));
        
        return;
    }

    if (cardToPlay->getCost() > players[playerID - 1]->getPlayerMagic()) {
        if (!players[playerID - 1]->getTesting() || cardToPlay->getCardType() != CardType::Spell) {
            // print error message not enough magic
            cout << "not enough magic" << endl;
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
            return;
        }
    }
    

    // use the effect/place it down
    if (cardToPlay->getCardType() == CardType::Minion) {
        if (static_cast<int>(minions[playerID - 1].size()) < MAX_MINIONS) {
            unique_ptr<Minion> minionToPlay = unique_ptr<Minion> (dynamic_cast<Minion*>(cardToPlay.release()));
            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() - minionToPlay->getCost());
            minions[playerID - 1].emplace_back(std::move(minionToPlay));
            notifyMinionEnter(playerID);
        } else {
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
            // error message for full minion board
            cout << "The board is full for minions" << endl;
        }
        
    } else if (cardToPlay->getCardType() == CardType::Ritual) {
        if (static_cast<int>(rituals[playerID - 1].size()) > 0) {
            unique_ptr<Card> discard = unique_ptr<Card> (static_cast<Card*>(rituals[playerID - 1][0].release()));
            discardedCards[playerID - 1].emplace_back(std::move(discard));
        }
        unique_ptr<Ritual> ritualToPlay = unique_ptr<Ritual> (dynamic_cast<Ritual*>(cardToPlay.release()));
        players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() - ritualToPlay->getCost());
        rituals[playerID - 1].emplace_back(std::move(ritualToPlay));

    } else if (cardToPlay->getCardType() == CardType::Spell) {
        Card &cardCast = *cardToPlay.get();
        Spell& spellCast = dynamic_cast<Spell&> (cardCast);

        try {
            if (targetType == TargetType::RitualTarget) {
                if (rituals[playerID - 1].size() > 0) {
                    Card &target = *rituals[playerID - 1][0];
                    spellCast.useSpell(*this, target);
                }
                
            } else if (targetType == TargetType::MinionTarget) {
                Card &target = *minions[playerID - 1][targetCard];
                spellCast.useSpell(*this, target);

            } else {
                spellCast.useSpell(*this);
            }

            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() - spellCast.getCost());

            // if testing mode and not enough magic
            if (players[playerID - 1]->getTesting() && players[playerID - 1]->getPlayerMagic() < 0) {
                players[playerID - 1]->setPlayerMagic(0);
            }
            discardedCards[playerID - 1].emplace_back(std::move(cardToPlay));
        } catch (std::logic_error &e) {
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
            // print error message, use printer class to do it later
            cout << e.what() << endl;
        }
        
    } else {
        if (targetCard != -1 && targetCard < static_cast<int> (minions[playerID - 1].size())) {
            unique_ptr<Enchantment> enchant = unique_ptr<Enchantment> (dynamic_cast<Enchantment*>(cardToPlay.release()));
            attach(std::move(enchant), playerID, targetCard);
        } else {
            //print error message no target
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
        }
        
    }
}

void Board::checkCardStates() {
    const int numPlayers = 2;
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < static_cast<int> (minions[i].size()); j++) {
            if (minions[i][j]->getReturnToHand()) {
                Card &targetNotify = static_cast<Card&>(*minions[i][j]);
                notifyMinionLeave(i, targetNotify);
                minions[i][j]->detachAllEnchant();
                
                unique_ptr<Card> card = unique_ptr<Card> (static_cast<Card*>(minions[i][j].release()));
                players[i]->returnToHand(std::move(card)); // not sure if I need to cast to Card
            
            } else if (minions[i][j]->getDefence() <= 0) {
                Card &targetNotify = static_cast<Card&> (*minions[i][j]);
                notifyMinionLeave(i, targetNotify);
                minions[i][j]->detachAllEnchant();
                players[i]->sendToGraveyard(std::move(minions[i][j]));
            }
        }

        if (static_cast<int> (rituals[i].size()) > 0) {
            if (rituals[i][0]->getReturnToHand() && players[i]->getHandSize() < MAX_HAND) {
                unique_ptr<Card> card = unique_ptr<Card> (static_cast<Card*>(rituals[i][0].release()));
                players[i]->returnToHand(std::move(card)); // not sure about cast again
            }
        }
    }
}

bool Board::summon(string card, int n, int playerID, int magicCost) {
    // if the board is full, reset magic cost and return false
    if (static_cast<int>(minions[playerID - 1].size()) == MAX_MINIONS) {
        players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() + magicCost);
        return false;
    }

    for (int i = 0; i < n; i++) {
        if (static_cast<int> (minions[playerID - 1].size()) < MAX_MINIONS) {
            // add minion to vector, either by creating new from string or std::move(card)
            minions[playerID - 1].emplace_back(static_cast<Minion*>((players[playerID - 1]->allocCard(card, playerID - 1)).release()));
            notifyMinionEnter(playerID);
        }
    }
    return true;
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
        for (int j = 0; j < static_cast<int> (minions[i].size()); j++) {
            if (!minions[i][j]->getSilenced()) minions[i][j]->notifyCardTurnStart(*this);
            else minions[i][j]->setActionCount(minions[i][j]->getActionReset());
        }

        if (static_cast<int> (rituals[i].size()) > 0 && rituals[i][0]->getCharges() < rituals[i][0]->getActionCost()) {
            rituals[i][0]->notifyCardTurnStart(*this);
        }
    }
}

void Board::notifyTurnEnd() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < static_cast<int> (minions[i].size()); j++) {
            if (!minions[i][j]->getSilenced()) minions[i][j]->notifyCardTurnEnd(*this);
        }

        if (static_cast<int> (rituals[i].size()) > 0 && rituals[i][0]->getCharges() < rituals[i][0]->getActionCost()) {
            rituals[i][0]->notifyCardTurnEnd(*this);
        }
    }
}

void Board::notifyMinionEnter(int playerID) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < static_cast<int> (minions[i].size()); j++) {
            if (!minions[i][j]->getSilenced()) {
                minions[i][j]->notifyCardMinionEnter(*this, *minions[playerID - 1][static_cast<int>(minions[playerID - 1].size()) - 1]);
            }
        }
        if (static_cast<int> (rituals[i].size()) > 0 && rituals[i][0]->getCharges() < rituals[i][0]->getActionCost()) {
            rituals[i][0]->notifyCardMinionEnter(*this, *minions[playerID - 1][static_cast<int> (minions[playerID - 1].size()) - 1]);
        }
    }
}

void Board::notifyMinionLeave(int playerID, Card &target) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < static_cast<int> (minions[i].size()); j++) {
            if (!minions[i][j]->getSilenced()) minions[i][j]->notifyCardMinionLeave(*this, target);
        }
        if (static_cast<int> (rituals[i].size()) > 0) {
            rituals[i][0]->notifyCardMinionEnter(*this, target);
        }
    }
}

Player& Board::getPlayer(int playerID) const {
    return *players[playerID - 1].get();
}

vector<vector<reference_wrapper<Card>>> Board::getMinions() const {
    vector<vector<reference_wrapper<Card>>> minionsCopy;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        vector<reference_wrapper<Card>> m {};
        minionsCopy.emplace_back(m);
        for (int j = 0; j < static_cast<int> (minions[i].size()); j++) {
            Card& m = static_cast<Card&>(*minions[i][j]);
            minionsCopy[i].emplace_back(m);
        }
    }
    return minionsCopy;
}

vector<vector<reference_wrapper<Ritual>>> Board::getRituals() const {
    vector<vector<reference_wrapper<Ritual>>> ritualsCopy;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        vector<reference_wrapper<Ritual>> r {};
        ritualsCopy.emplace_back(r);
        if (static_cast<int> (rituals[i].size()) > 0) {
            ritualsCopy[i].emplace_back(*rituals[i][0]);
        }
    }
    return ritualsCopy;
}

vector<reference_wrapper<Minion>> Board::getGraveyard(int playerID) const {
    return players[playerID - 1]->getGraveyard();
}

void Board::startCommand(int playerID) {
    addMagic(playerID, 1);
    players[playerID - 1]->drawCard(); // checking for hand size and deck size is done in player
    notifyTurnStart();
}

void Board::endCommand() {
    notifyTurnEnd();
}

void Board::attackCommand(int minionInd, int playerID, int enemyMinion) {
    int enemyPlayer = (playerID == 1) ? 2 : 1;
    if (minions[playerID - 1][minionInd]->getActionCount() <= 0) {
        // print error not enough actions on minion
        cout << "Not enough actions to attack" << endl;
        return;
    }
    
    if (enemyMinion != -1) {
        minions[playerID - 1][minionInd]->attack(*minions[enemyPlayer - 1][minionInd]);
    } else {
        minions[playerID - 1][minionInd]->attack(*players[enemyPlayer - 1]);
    }
    minions[playerID - 1][minionInd]->setActionCount(minions[playerID - 1][minionInd]->getActionCount() - 1);
}

void Board::useMinionAbilityCommand(int minionInd, int playerID, int targetPlayer, int targetCard) {
    if (players[playerID - 1]->getPlayerMagic() < minions[playerID - 1][minionInd]->getActivationCost() && !players[playerID - 1]->getTesting()) {
        // print error message, not enough magic
        cout << "Not enough Magic" << endl;
        return;
    } else if (minions[playerID - 1][minionInd]->getActionCount() < 1) {
        // print error message, no more actions
        cout << "Not enough actions to use ability" << endl;
        return;
    } else if (minions[playerID - 1][minionInd]->getSilenced()) {
        // print error message, minion is silenced
        cout << minions[playerID - 1][minionInd]->getName() << " is silenced, the ability will not activate." << endl;
        return;
    }

    if (targetCard == 'r') {
        // minions[playerID - 1][minionInd]->activateAbility(*this, *rituals[targetPlayer - 1][0]);
        // print error message for now because we don't have any cards that do this
        cout << "Ritual is not a valid target" << endl;
    } else {
        if (targetCard == -1) {
            minions[playerID - 1][minionInd]->activateAbility(*this);
            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() -  minions[playerID - 1][minionInd]->getActivationCost());
            
            if (players[playerID - 1]->getPlayerMagic() < 0 && players[playerID - 1]->getTesting()) {
                players[playerID - 1]->setPlayerMagic(0);
            }

        } else if (targetCard >= 0 && targetCard <static_cast<int> (minions[playerID - 1].size())) {
            minions[playerID - 1][minionInd]->activateAbility(*this, *minions[targetPlayer - 1][targetCard]);
            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() -  minions[playerID - 1][minionInd]->getActivationCost());
            
            if (players[playerID - 1]->getPlayerMagic() < 0 && players[playerID - 1]->getTesting()) {
                players[playerID - 1]->setPlayerMagic(0);
            }
        }
    }
}

void Board::increaseRitualCharges(int playerID, int amount) {
    rituals[playerID - 1][0]->setCharges(rituals[playerID - 1][0]->getCharges() + amount);
}

void Board::raiseDead(int playerID) {
    if (static_cast<int> (players[playerID - 1]->getGraveyard().size()) > 0) {
        if (static_cast<int> (minions[playerID - 1].size()) < MAX_MINIONS) {
            unique_ptr<Minion> raisedMinion = players[playerID - 1]->returnTopFromGraveyard();
            raisedMinion->setDefence(1);
            minions[playerID - 1].emplace_back(std::move(raisedMinion));
        }
    } else {
        throw std::logic_error("Raise Dead cannot be played with no cards in graveyard");
    }
}

void Board::removeRitual(int playerTarget) {
    if (static_cast<int> (rituals[playerTarget].size()) > 0) {
        unique_ptr<Card> card = unique_ptr<Card> (static_cast<Card*>(rituals[playerTarget][0].release()));
        discardedCards[playerTarget - 1].emplace_back(std::move(card));
    } else {
        // print error message
        throw logic_error("There is no ritual to target.");
    }
    
}

void Board::addMagic(int playerID, int magic) {
    players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() + magic);
}

void Board::rechargeRitual(int playerID, int charges) {
    if (static_cast<int>(rituals[playerID - 1].size()) > 0) {
        rituals[playerID - 1][0]->setCharges(rituals[playerID - 1][0]->getCharges() + charges);
    } else {
        throw logic_error("Cannot play Recharge with no Ritual on Board");
        // print error message
    }
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
