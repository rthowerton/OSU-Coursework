//hand class. Each hand has a list of cards initialized to 11 and a number of cards in the list
class hand{
   private:
      card* cards;
      int numCards;//for some reason numCards is not being stored properly when card is added.
   public:
      hand();//default constructor
      ~hand();//deconstructor
      void setCards(int);//set the list of cards to a size, updates numCards
      void addCard(card);//add a card to the hand
      card* getCardsList();//returns list of cards for viewing
      int getNumCards();//access numCards
      void resetHand();//reset hand
};
