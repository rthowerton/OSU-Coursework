#ifndef TIGER_HEADER
#define TIGER_HEADER
#include "animal.h"
class tiger : public animal{
   public:
      tiger();
      void operator=(const tiger&);
};
#endif
