#include "deck.h"
class game{
   private:
      deck theDeck;
      player* players;
      dealer house;
      int numPlayers;
   public:
      game();
      game(int);
      ~game();
      int getNumPlayers();
      void setPlayers(int);
      void playGame();
};
