#include <iostream>
using std::cout;
using std::endl;
#include "event.h"
#include "bats.h"
//bats constructor
bats::bats(){
   type = 'b';
   message = "You hear wings flapping.\n";
}
//near()
void bats::near(){
   cout<<message<<endl;
}
