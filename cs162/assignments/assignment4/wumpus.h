#ifndef WUMPUS_HEADER
#define WUMPUS_HEADER
class wumpus : public event{
   private:
      int wRow, wCol;
   public:
      wumpus();
      void near();
      int getRow();
      int getCol();
      void setRow(int);
      void setCol(int);
};
#endif
