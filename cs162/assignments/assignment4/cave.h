#ifndef CAVE_HEADER
#define CAVE_HEADER
#include "room.h"
#include "player.h"
#include "wumpus.h"
class cave{
   protected:
      room** lair;
      int numRows, numCols;
      struct player jeremy;
      wumpus wump;
      bool isWumpus, isPlayer, hasWon;
   public:
      cave();
      cave(int, int);
      ~cave();
      void allocateStuff();
      void placePlayer();
      void drawCave();
      void callPercepts();
      void movePlayer();
      void shootArrow();
      void notBad();
      void gitGud();
      void moveWumpus();
      void pitStop();
      void batnapping();
      void getGold();
      bool playerLives();
      bool winCondition();
};
#endif
