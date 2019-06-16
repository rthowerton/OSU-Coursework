//deck class contains a stack of 52 cards and an index for current card
class deck{
   private:
      card cards[52];//deck of cards
      int currentCard;//index
   public:
      deck();//default constructor
      ~deck();//destructor
      void shuffleDeck();//shuffle deck
      void dealCard(hand, card);//deal a card to a hand
      card getCurrentCard();//access card at current index
      card getNextCard();//get the next card in the deck
      void resetCurrentCard();
};
