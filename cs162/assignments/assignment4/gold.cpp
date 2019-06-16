#include <iostream>
using std::cout;
using std::endl;
#include "event.h"
#include "gold.h"
//gold constructor
gold::gold(){
   type = 'g';
   message = "You see a glimmer all around you.\n";
}
//near()
void gold::near(){
   cout<<message<<endl;
}
void gold::setRow(int y){
   gRow = y;
}

void gold::setCol(int x){
   gCol = x;
}
