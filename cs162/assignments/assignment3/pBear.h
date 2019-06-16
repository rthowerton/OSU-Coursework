#ifndef PBEAR_HEADER
#define PBEAR_HEADER
#include "animal.h"
class pBear : public animal{
   public:
      pBear();
      void operator=(const pBear&);
};
#endif
