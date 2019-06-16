#ifndef ROPE_HEADER
#define ROPE_HEADER
#include "event.h"
class rope : public event{
   private:
      int rRow, rCol;
   public:
      rope();
      void near();
      void setRow(int);
      void setCol(int);
};
#endif
