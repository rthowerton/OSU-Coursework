#include "penguin.h"
//constructor
penguin::penguin(){
   age = 0;
   cost = 1000;
   numBabies = 3;
   foodCost = 10;
}
//operator overload
void penguin::operator=(const penguin& p){
   age = p.age;
   cost = p.cost;
   numBabies = p.numBabies;
   foodCost = p.foodCost;
}
