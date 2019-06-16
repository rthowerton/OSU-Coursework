class dealer{
   private:
      hand dHand;
      int cardTotal;
   public:
      dealer();
      ~dealer();
      hand getDealerHand();
      int getCardTotal();
      void addCardTotal(int);
      void resetCardTotal();
};
