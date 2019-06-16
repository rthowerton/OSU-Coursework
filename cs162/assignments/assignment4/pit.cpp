#include <iostream>
using std::cout;
using std::endl;
#include "event.h"
#include "pit.h"
//pit constructor
pit::pit(){
   type = 'p';
   message = "You feel a strong breeze.\n";
}
//near()
void pit::near(){
   cout<<message<<endl;
}
