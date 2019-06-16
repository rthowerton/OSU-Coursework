#ifndef PENGUIN_HEADER
#define pENGUIN_HEADER
#include "animal.h"
class penguin : public animal{
   public:
      penguin();
      void operator=(const penguin&);
};
#endif
