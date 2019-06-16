#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"
#include "rope.h"
#include "nothing.h"
#include "room.h"
//room constructor
room::room(){
   e = new nothing();
   hasPlayer = false;
}
//deconstructor
room::~room(){
   delete e;
}

event* room::getEvent(){
   return e;
}
//call event percept
void room::percept(){
   e->near();
}
//player is in room
void room::doesHavePlayer(){
   hasPlayer = true;
}
//check if player is in room
bool room::isInRoom(){
   return hasPlayer;
}
