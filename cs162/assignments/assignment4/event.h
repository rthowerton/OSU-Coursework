#ifndef EVENT_HEADER
#define EVENT_HEADER
#include <iostream>
using std::string;
class event{
   protected:
      char type;
      string message;
   public:
      virtual void near() = 0;
      void operator = (const event*);
      char getType();
      void changeEvent(event*);
};
#endif
