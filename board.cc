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
            notifyMinionEnter();
        } else {
            players[playerID - 1]->returnToHand(cardToPlay);
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
        unique_ptr<Enchantment> enchant {dynamic_cast<Enchantment*>(std::move(cardToPlay))};
        minions[playerID - 1][targetCard]->attachEnchant(enchant);
    }
}

void Board::summon(unique_ptr<Card> card, int n) {}

void Board::attach(unique_ptr<Card> card) {}

void Board::detach(unique_ptr<Card> card) {}

void Board::notifyTurnStart() {
    const int numPlayers = 2;
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardTurnStart();
        }
    }
}

void Board::notifyTurnEnd() {
    const int numPlayers = 2;
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardTurnEnd();
        }
    }
}

void Board::notifyMinionEnter() {
    const int numPlayers = 2;
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardMinionEnter();
        }
    }
}

void Board::notifyMinionLeave() {
    const int numPlayers = 2;
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < minions[i].size(); j++) {
            minions[i][j]->notifyCardTurnStart();
        }
    }
}

Player Board::getPlayer(int playerID) {
    return *players[playerID - 1];
}

vector<vector<Minion&>> Board::getMinions() {
    // return minions;
}

vector<vector<Ritual&>> Board::getRituals() {
    // return rituals;
}

vector<Card&> Board::getGraveyard(int playerID) {
    // return players[playerID]->getGraveyard();
}

void Board::endCommand() {

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
        minions[playerID - 1][minionInd]->activateAbility(*this, rituals[targetPlayer - 1][0]);
    } else if (targetCard == -1) {
        minions[playerID - 1][minionInd]->activateAbility(*this);
    } else {
        minions[playerID - 1][minionInd]->activateAbility(*this, minions[targetPlayer - 1][targetCard]);
    }
}

void Board::increaseRitualCharges(int playerID, int amount) {

}

void Board::raiseDead() {

}

void Board::removeRitual() {
    
}
