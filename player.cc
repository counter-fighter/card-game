#include "player.h"

unique_ptr<Card> allocCard (string name, int id) {
  if (name == "Giant Strength") return unique_ptr<Card> {new GiantStrength(id)};
  if (name == "Enrage") return unique_ptr<Card> {new Enrage(id)};
  if (name == "Haste") return unique_ptr<Card> {new Haste(id)};
  if (name == "Magic Fatigue") return unique_ptr<Card> {new MagicFatigue(id)};
  if (name == "Silence") return unique_ptr<Card> {new Silence(id)};
  if (name == "Air Elemental") return unique_ptr<Card> {new AirElemental(id)};
  if (name == "Earth Elemental") return unique_ptr<Card> {new EarthElemental(id)};
  if (name == "Bone Golem") return unique_ptr<Card> {new BoneGolem(id)};
  if (name == "Fire Elemental") return unique_ptr<Card> {new FireElemental(id)};
  if (name == "Potion Seller") return unique_ptr<Card> {new PotionSeller(id)};
  if (name == "Novice Pyromancer") return unique_ptr<Card> {new NovicePyromancer(id)};
  if (name == "Apprentice Summoner") return unique_ptr<Card> {new ApprenticeSummoner(id)};
  if (name == "Master Summoner") return unique_ptr<Card> {new MasterSummoner(id)};
  if (name == "Dark Ritual") return unique_ptr<Card> {new DarkRitual(id)};
  if (name == "Aura of Power") return unique_ptr<Card> {new AuraOfPower(id)};
  if (name == "Standstill") return unique_ptr<Card> {new Standstill(id)};
  if (name == "Banish") return unique_ptr<Card> {new Banish(id)};
  if (name == "Unsummon") return unique_ptr<Card> {new Unsummon(id)};
  if (name == "Recharge") return unique_ptr<Card> {new Recharge(id)};
  if (name == "Disenchant") return unique_ptr<Card> {new Disenchant(id)};
  if (name == "Raise Dead") return unique_ptr<Card> {new RaiseDead(id)};
  if (name == "Blizzard") return unique_ptr<Card> {new Blizzard(id)};
  return nullptr;
}

Player::~Player() {};


Player::Player(string name, int id, string filename, bool shuffle): 
name{name}, id{id}, magic{MAGIC_RESET}, health{HEALTH_RESET}, deck{}, hand{}, graveyard{} {
  ifstream ifs(filename);
  string line;
  while (getline(ifs, line)) {
    deck.emplace_back(move(allocCard(line, id)));
  }

  if (shuffle) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine rng{seed};

    for ( int i = 0; i < 1000; i++ ) {
      std::shuffle( deck.begin(), deck.end(), rng );
    }
  }

};

vector<Minion&> Player::getGraveyard() {
  vector<Minion&> ret;

  for (auto it = graveyard.begin(); it != graveyard.end(); it++) {
    ret.emplace_back(*(*it).get());
  }

  return ret;
};

int Player::getPlayerId() { return id; };

string Player::getPlayerName() { return name; };

int Player::getPlayerHealth() { return health; };

int Player::getPlayerMagic() { return magic; };

void Player::setPlayerHealth(int n) { health = n; };

bool Player::drawCard() {
  if ((int)hand.size() < MAX_HAND) {
    hand.emplace_back(deck.back());
    deck.pop_back();
  }
};

unique_ptr<Card> Player::playFromHand (int index) {
  if (index >= 0 && index < (int)hand.size()) {
    unique_ptr<Card> temp = move(hand[index]);
    hand.erase(hand.begin() + index);
    return move(temp);
  }
};

void Player::sendToGraveyard(unique_ptr<Minion> m) {
  graveyard.emplace_back(move(m));
};

bool Player::returnToHand(unique_ptr<Card> c) {
  if ((int)hand.size() >= MAX_HAND) return false;
  hand.emplace_back(move(c));
  return true;
};
