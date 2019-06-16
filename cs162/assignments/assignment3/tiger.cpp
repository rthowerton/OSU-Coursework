#include "tiger.h"
//constructor
tiger::tiger(){
   age = 0;
   cost = 10000;
   numBabies = 1;
   foodCost = 50;
}
//operator overload
void tiger::operator=(const tiger& t){
   age = t.age;
   cost = t.cost;
   numBabies = t.numBabies;
   foodCost = t.foodCost;
}
