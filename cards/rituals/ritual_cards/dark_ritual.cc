#include "dark_ritual.h"


DarkRitual::DarkRitual(int player) : Ritual{"Dark Ritual", "At the start of your turn, gain 1 magic", 0, player, 5, 1} {};

DarkRitual::~DarkRitual() {};

void DarkRitual::notifyCardTurnStart(Board &brd) {
  // brd.addMagic();
};


