#include "pBear.h"
//constructor
pBear::pBear(){
   age = 0;
   cost =5000;
   numBabies = 2;
   foodCost = 30;
}
//operator overload
void pBear::operator=(const pBear& b){
   age = b.age;
   cost = b.cost;
   numBabies = b.numBabies;
   foodCost = b.foodCost;
}
