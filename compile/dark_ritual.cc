#include "dark_ritual.h"
#include "board.h"

DarkRitual::DarkRitual(int player) : Ritual{"Dark Ritual", "At the start of your turn, gain 1 magic", 0, player, 5, 1} {};

DarkRitual::~DarkRitual() {};

// Only triggers if charges are sufficient
void DarkRitual::notifyCardTurnStart(Board &brd) {
  if (charges >= actCost) {
    brd.addMagic(player, 1);
    charges -= actCost;
  }
};


