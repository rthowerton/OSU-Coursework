//player class has a personal hand, current money, total value of cards in hand, and current bet
class player{
   private:
      hand pHand;//player's hand
      int playerMoney;//player's current money
      int cardTotal;//total value of cards in hand
      int bet;//current bet
   public:
      player();//default constructor
      ~player();//destructor
      hand getPlayerHand();//return player's unique hand
      int getPlayerMoney();//access player's money
      int getCardTotal();//access value of cards in hand
      int getBet();//access player's bet
      void changePlayerMoney(int);//edit the player's money
      void addCardTotal(int);//add card value to hand
      void addBet(int);//increase player's bet
      void resetCardTotal();//reset card total to 0
};
