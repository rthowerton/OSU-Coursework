#include "card.h"
class deck{
   private:
      card cards[52];
      int numCards;
   public:
      void setCards(card*);
      void assignType(int, int);
      void zeroDeck(card*);
      void shuffle(int);
      deck makeDeck();
};
