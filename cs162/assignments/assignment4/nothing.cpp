#include <iostream>
using std::cout;
using std::endl;
#include "event.h"
#include "nothing.h"
//nothing constructor
nothing::nothing(){
   type = ' ';
   message = "";
}
//near()
void nothing::near(){
   cout<<message;
}
