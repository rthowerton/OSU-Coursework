#include <iostream>
using std::cout;
using std::endl;
#include "event.h"
#include "wumpus.h"
//wumpus constructor
wumpus::wumpus(){
   type = 'w';
   message = "You smell a horrible stench.\n";
}
//near()
void wumpus::near(){
   cout<<message<<endl;
}


int wumpus::getRow(){
   return wRow;
}

int wumpus::getCol(){
   return wCol;
}

void wumpus::setRow(int y){
   wRow = y;
}

void wumpus::setCol(int x){
   wCol = x;
}
