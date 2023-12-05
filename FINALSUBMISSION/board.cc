#include "board.h"

// =========================================================================
//                      Board Object Initialization
// =========================================================================

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


// =========================================================================
//                         Main Play Card Funnel
// =========================================================================

// targetPlayer and targetCard defaults to -1 if no input given
// Returns true if changes require a call to checkCardState, false O.W.
bool Board::playACard(int cardInd, int playerID, int targetPlayer, int targetCard) {
    TargetType targetType = TargetType::NoTarget;
    
    if (targetPlayer == -1) targetPlayer = playerID;

    if (targetCard != -1) {
        if (targetCard == 'r') {
            targetType = TargetType::RitualTarget;
        } else {
            targetType = TargetType::MinionTarget;
        }
    }

    unique_ptr<Card> cardToPlay = players[playerID - 1]->playFromHand(cardInd);

    // Checks for sufficient arguments
    if (targetType != cardToPlay->getTargetType() && cardToPlay->getTargetType() != TargetType::AllTarget) {
        // print error message wrong args
        players[playerID - 1]->returnToHand(std::move(cardToPlay));
        throw std::logic_error("Incorrect arguments");
        return false;
    }

    // Checks for sufficient magic
    if (cardToPlay->getCost() > players[playerID - 1]->getPlayerMagic() && !players[playerID - 1]->getTesting()) {
        // print error message not enough magic
        players[playerID - 1]->returnToHand(std::move(cardToPlay));
        throw std::logic_error("not enough magic");
    }
    

    // use the effect/place it down
    // -------------------------------------------------------------------------
    //                              Minion cond
    // -------------------------------------------------------------------------
    if (cardToPlay->getCardType() == CardType::Minion) {
        if (static_cast<int>(minions[playerID - 1].size()) < MAX_MINIONS) {
            unique_ptr<Minion> minionToPlay = unique_ptr<Minion> (dynamic_cast<Minion*>(cardToPlay.release()));
            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() - minionToPlay->getCost());

            // if testing mode and not enough magic
            if (players[playerID - 1]->getTesting() && players[playerID - 1]->getPlayerMagic() < 0) {
                players[playerID - 1]->setPlayerMagic(0);
            }

            minions[playerID - 1].emplace_back(std::move(minionToPlay));
            notifyMinionEnter(playerID);
            return true;
        } else {
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
            return false;
        }
        
    // -------------------------------------------------------------------------
    //                              Ritual cond
    // -------------------------------------------------------------------------
    } else if (cardToPlay->getCardType() == CardType::Ritual) {
        if (static_cast<int>(rituals[playerID - 1].size()) > 0) {
            unique_ptr<Card> discard = unique_ptr<Card> (static_cast<Card*>(rituals[playerID - 1][0].release()));
            rituals[playerID - 1].pop_back();
            discardedCards[playerID - 1].emplace_back(std::move(discard));
        }
        unique_ptr<Ritual> ritualToPlay = unique_ptr<Ritual> (dynamic_cast<Ritual*>(cardToPlay.release()));
        players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() - ritualToPlay->getCost());

        // if testing mode and not enough magic
        if (players[playerID - 1]->getTesting() && players[playerID - 1]->getPlayerMagic() < 0) {
            players[playerID - 1]->setPlayerMagic(0);
        }

        rituals[playerID - 1].emplace_back(std::move(ritualToPlay));
        return true;

    // -------------------------------------------------------------------------
    //                              Spell cond
    // -------------------------------------------------------------------------
    } else if (cardToPlay->getCardType() == CardType::Spell) {
        Card &cardCast = *cardToPlay.get();
        Spell& spellCast = dynamic_cast<Spell&> (cardCast);

        try {
            if (targetType == TargetType::RitualTarget) {
                if (rituals[playerID - 1].size() > 0) {
                    Card &target = *rituals[targetPlayer - 1][0];
                    spellCast.useSpell(*this, target);
                }
                
            } else if (targetType == TargetType::MinionTarget) {
                Card &target = *minions[targetPlayer - 1][targetCard];
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

            return true;
        } catch (std::logic_error &e) {
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
            // print error message
            throw;
        }
        
    // -------------------------------------------------------------------------
    //                            Enchantment cond
    // -------------------------------------------------------------------------
    } else {
        if (targetCard != -1 && targetCard < static_cast<int> (minions[targetPlayer - 1].size())) {
            unique_ptr<Enchantment> enchant = unique_ptr<Enchantment> (dynamic_cast<Enchantment*>(cardToPlay.release()));
            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() - enchant->getCost());
            attach(std::move(enchant), targetPlayer, targetCard);

            // if testing mode and not enough magic
            if (players[playerID - 1]->getTesting() && players[playerID - 1]->getPlayerMagic() < 0) {
                players[playerID - 1]->setPlayerMagic(0);
            }
            return true;

        } else {
            //print error message no target
            players[playerID - 1]->returnToHand(std::move(cardToPlay));
            throw std::logic_error("Incorrect target index");
        }
        
    }
    return false;
}

// =========================================================================
//                         Notify functions (Observers)
// =========================================================================

void Board::notifyTurnStart(int playerID) {
    int ID = playerID - 1;
    for (int j = 0; j < static_cast<int> (minions[ID].size()); j++) {
        if (!minions[ID][j]->getSilenced()) minions[ID][j]->notifyCardTurnStart(*this);
        else minions[ID][j]->setActionCount(minions[ID][j]->getActionReset());
    }

    if (static_cast<int> (rituals[ID].size()) > 0 && rituals[ID][0]->getCharges() >= rituals[ID][0]->getActionCost()) {
        rituals[ID][0]->notifyCardTurnStart(*this);
    }
}

void Board::notifyTurnEnd(int playerID) {
    int ID = playerID - 1;
    for (int j = 0; j < static_cast<int> (minions[ID].size()); j++) {
        if (!minions[ID][j]->getSilenced()) minions[ID][j]->notifyCardTurnEnd(*this);
    }

    if (static_cast<int> (rituals[ID].size()) > 0 && rituals[ID][0]->getCharges() >= rituals[ID][0]->getActionCost()) {
        rituals[ID][0]->notifyCardTurnEnd(*this);
    }
}

void Board::notifyMinionEnter(int playerID) {
    int ID = playerID - 1;
    int counter = 0;
    while (counter <= 1) {
        for (int j = 0; j < static_cast<int> (minions[ID].size()); j++) {
            if (!minions[ID][j]->getSilenced()) {
                minions[ID][j]->notifyCardMinionEnter(*this, *minions[playerID - 1][static_cast<int>(minions[playerID - 1].size()) - 1]);
            }
        }
        if (static_cast<int> (rituals[ID].size()) > 0 && rituals[ID][0]->getCharges() >= rituals[ID][0]->getActionCost()) {
            rituals[ID][0]->notifyCardMinionEnter(*this, *minions[playerID - 1][static_cast<int> (minions[playerID - 1].size()) - 1]);
        }
        ID = (playerID == 1) ? 1 : 0;
        counter++;
    }
}

void Board::notifyMinionLeave(int playerID, Card &target) {
    int ID = playerID - 1;
    int counter = 0;
    while (counter <= 1) {
        for (int j = 0; j < static_cast<int> (minions[ID].size()); j++) {
            if (!minions[ID][j]->getSilenced()) minions[ID][j]->notifyCardMinionLeave(*this, target);
        }
        if (static_cast<int> (rituals[ID].size()) > 0 && rituals[ID][0]->getCharges() >= rituals[ID][0]->getActionCost()) {
            rituals[ID][0]->notifyCardMinionLeave(*this, target);
        }
        ID = (playerID == 1) ? 1 : 0;
        counter++;
    }
}

// =========================================================================
//                     Functions to return to printer
// =========================================================================

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

// =========================================================================
//                     Main control flow functions
// =========================================================================

void Board::startCommand(int playerID) {
    addMagic(playerID, 1);
    players[playerID - 1]->drawCard(); // checking for hand size and deck size is done in player
    notifyTurnStart(playerID);
}

void Board::endCommand(int playerID) {
    notifyTurnEnd(playerID);
}

bool Board::attackCommand(int minionInd, int playerID, int enemyMinion) {
    int enemyPlayer = (playerID == 1) ? 2 : 1;
    if (minions[playerID - 1][minionInd]->getActionCount() <= 0) {
        // print error not enough actions on minion
        throw std::logic_error("Not enough actions to attack");
    }
    
    if (enemyMinion != -1) {
        minions[playerID - 1][minionInd]->attack(*minions[enemyPlayer - 1][enemyMinion]);
    } else {
        minions[playerID - 1][minionInd]->attack(*players[enemyPlayer - 1]);
    }

    return true;
}

bool Board::useMinionAbilityCommand(int minionInd, int playerID, int targetPlayer, int targetCard) {
    if (players[playerID - 1]->getPlayerMagic() < minions[playerID - 1][minionInd]->getActivationCost() && !players[playerID - 1]->getTesting()) {
        // print error message, not enough magic
        throw std::logic_error("Not enough Magic");
    } else if (minions[playerID - 1][minionInd]->getActionCount() < 1 && !players[playerID - 1]->getTesting()) {
        // print error message, no more actions
        throw std::logic_error("Not enough actions to use ability");
    } else if (minions[playerID - 1][minionInd]->getSilenced()) {
        // print error message, minion is silenced
        throw std::logic_error("Minion is silenced, the ability will not activate.");
    }

    if (targetCard == 'r') {
        // print error message for now because we don't have any cards that do this
        throw std::logic_error("Ritual is not a valid target");
    } else if (minions[playerID - 1][minionInd]->getActionCount() >= 1){
        if (targetCard == -1) {
            minions[playerID - 1][minionInd]->activateAbility(*this);
            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() -  minions[playerID - 1][minionInd]->getActivationCost());
            
        } else if (targetCard >= 0 && targetCard <static_cast<int> (minions[playerID - 1].size())) {
            minions[playerID - 1][minionInd]->activateAbility(*this, *minions[targetPlayer - 1][targetCard]);
            players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() -  minions[playerID - 1][minionInd]->getActivationCost());
    
        }

        // if testing mode and not enough magic
        if (players[playerID - 1]->getPlayerMagic() < 0 && players[playerID - 1]->getTesting()) {
            players[playerID - 1]->setPlayerMagic(0);
        }

        return true;
    
    } else {
        throw std::logic_error("Not enough enough actions to use ability");
    }

    return false;
}

// Runs through the whole board and discard cards that need to be discarded
void Board::checkCardStates(int playerID) {
    int ID = playerID - 1;
    string e;
    for (int j = 0; j < static_cast<int> (minions[ID].size()); j++) {
        Minion &target = *minions[ID][j];
        Card &targetNotify = static_cast<Card&>(*minions[ID][j]);
        if (target.getReturnToHand() && players[ID]->getHandSize() < MAX_HAND) {
            notifyMinionLeave(playerID, targetNotify);
            target.detachAllEnchant();
            target.setReturnToHand(false);
                
            unique_ptr<Card> card = unique_ptr<Card> (static_cast<Card*>(minions[ID][j].release()));
            minions[ID].erase(minions[ID].begin() + j);
            players[ID]->returnToHand(std::move(card)); // not sure if I need to cast to Card
                
        } else if (target.getBannished()) {
            notifyMinionLeave(playerID, targetNotify);
            target.detachAllEnchant();
            target.setBannished(false);
            players[ID]->sendToGraveyard(std::move(minions[ID][j]));
            minions[ID].erase(minions[ID].begin() + j);
            j--;

        } else if (target.getDefence() <= 0 || (target.getReturnToHand() && players[ID]->getHandSize() >= MAX_HAND)) {
            if (target.getReturnToHand()) e = "hand is full, card discarded";
            notifyMinionLeave(playerID, targetNotify);
            target.detachAllEnchant();
            players[ID]->sendToGraveyard(std::move(minions[ID][j]));
            minions[ID].erase(minions[ID].begin() + j);
        }
    }
    

    if (static_cast<int> (rituals[ID].size()) > 0) {
        if (rituals[ID][0]->getReturnToHand()) {
                unique_ptr<Card> card = unique_ptr<Card> (static_cast<Card*>(rituals[ID][0].release()));
                rituals[ID].pop_back();
            if (players[ID]->getHandSize() < MAX_HAND) {
                players[ID]->returnToHand(std::move(card));
            } else {
                e = "hand is full, card discarded";
            }
        }
    }

    if (e != "") {
        throw std::logic_error(e);
    }
}

// =========================================================================
//                             Functions for Cards
// =========================================================================

bool Board::summon(string card, int n, int playerID, int magicCost) {
    // if the board is full, reset magic cost and return false
    if (static_cast<int>(minions[playerID - 1].size()) >= MAX_MINIONS || magicCost == -1) {
        players[playerID - 1]->setPlayerMagic(players[playerID - 1]->getPlayerMagic() + magicCost);
        throw std::logic_error("Board is full. Failed to summon.");
    }

    for (int i = 0; i < n; i++) {
        if (static_cast<int> (minions[playerID - 1].size()) < MAX_MINIONS) {
            // add minion to vector, either by creating new from string or std::move(card)
            minions[playerID - 1].emplace_back(static_cast<Minion*>((players[playerID - 1]->allocCard(card, playerID)).release()));
            notifyMinionEnter(playerID);
        }
    }
    return true;
}

void Board::attach(unique_ptr<Card> card, int playerID, int targetCard) {
    unique_ptr<Enchantment> enchant = unique_ptr<Enchantment> (dynamic_cast<Enchantment*>(card.release()));
    minions[playerID - 1][targetCard]->attachEnchant(std::move(enchant));
}

void Board::detach(int playerID, int targetCard) {
    minions[playerID - 1][targetCard]->detachEnchant();
}

void Board::raiseDead(int playerID) {
    if (static_cast<int> (players[playerID - 1]->getGraveyard().size()) > 0) {
        if (static_cast<int> (minions[playerID - 1].size()) < MAX_MINIONS) {
            unique_ptr<Minion> raisedMinion = players[playerID - 1]->returnTopFromGraveyard();
            raisedMinion->setDefence(1);
            minions[playerID - 1].emplace_back(std::move(raisedMinion));
        } else {
            throw std::logic_error("Raise Dead cannot be played when board is full");
        }
    } else {
        throw std::logic_error("Raise Dead cannot be played with no cards in graveyard");
    }
}

void Board::removeRitual(int playerTarget) {
    if (static_cast<int> (rituals[playerTarget].size()) > 0) {
        unique_ptr<Card> card = unique_ptr<Card> (static_cast<Card*>(rituals[playerTarget][0].release()));
        rituals[playerTarget].pop_back();
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

void Board::healAllPlayer(int n, int playerID) {
    const int p = playerID - 1;
    int minionSizeP = minions[p].size();
    for (int i = 0; i < minionSizeP; i++) {
        minions[p][i]->setDefence(minions[p][i]->getDefence() + n);
    }

}
