#ifndef GOLD_HEADER
#define GOLD_HEADER
class gold : public event{
   private:
      int gRow, gCol;
   public:
      gold();
      void near();
      void setRow(int);
      void setCol(int);
};
#endif
