#ifndef ZOO_HEADER
#define ZOO_HEADER
#include "animal.h"
#include "tiger.h"
#include "pBear.h"
#include "penguin.h"
class zoo{
   private:
      int funds, numTigers, numBears, numPenguins;
      tiger* tigers;
      pBear* pBears;
      penguin* penguins;
   public:
      zoo();
      ~zoo();
      int getFunds();
      int getNumTigers();
      int getNumBears();
      int getNumPenguins();
      void changeMoney(int);
      void buyAnimal();
      void death();
      void bonus();
      void birth();
      void randomEvent();
      void activateDay();
      void playGame();
};
#endif
