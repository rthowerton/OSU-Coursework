//using enum for keeping track of suits
enum cardSuit {spades = 0, clubs = 1, hearts = 2, diamonds = 3};
//card class. Each card has a value between 1 and 13 and a suit, listed above
class card{
   private:
      int value;
      cardSuit suit;
   public:
      card();//default constructor
      ~card();//destructor
      void operator=(const card&);//assignment operator overload
      int getValue();//access card value
      cardSuit getSuit();//access card suit
      void setValue(int);//set a card's value
      void setSuit(cardSuit);//set a card's suit
};
