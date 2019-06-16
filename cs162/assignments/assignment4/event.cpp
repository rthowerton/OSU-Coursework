#include <iostream>
#include "event.h"
void event::operator = (const event* e){
   this->type = e->type;
}

char event::getType(){
   return type;
}

void event::changeEvent(event* e){
   this->type = e->type;
   this->message = e->message;
}
