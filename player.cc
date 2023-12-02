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

void f(Card &c) {
  cout <<  c.getName() << endl;
}

Player::Player(string name, int id, ifstream &ifs): 
name{name}, id{id}, magic{MAGIC_RESET}, health{HEALTH_RESET}, deck{}, hand{}, graveyard{} {
  string line;
  while (getline(ifs, line)) {
    cout << line << endl;
    deck.emplace_back(move(allocCard(line, id)));
    //shared_ptr<Card> c {new GiantStrength(1)};
    f(*deck.back().get());
  }
};


