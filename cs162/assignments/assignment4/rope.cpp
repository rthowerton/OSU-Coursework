#include <iostream>
#include "rope.h"
//rope constructor
rope::rope(){
   type = 'r';
   message = "";
}
//near
void rope::near(){
   return;
}

void rope::setRow(int y){
   rRow = y;
}

void rope::setCol(int x){
   rCol = x;
}
