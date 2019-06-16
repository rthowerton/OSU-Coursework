#ifndef ROOM_HEADER
#define ROOM_HEADER
#include "event.h"
class room{
   protected:
      event* e;
      bool hasPlayer;
   public:
      room();
      ~room();
      event* getEvent();
      void percept();
      void doesHavePlayer();
      bool isInRoom();
};
#endif
