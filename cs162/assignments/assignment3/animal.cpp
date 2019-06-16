#include "animal.h"
//constructor
animal::animal(){
   age = 0;
   cost = 0;
   numBabies = 0;
   foodCost = 10;
}
//operator overload
void animal::operator=(const animal& a){
   age = a.age;
   cost = a.cost;
   numBabies = a.numBabies;
   foodCost = a.foodCost;
}
/*
 * Function: getAge()
 * Description: return animal's age
 * Parameters: none
 * Pre-Conditions: animal is initialized
 * Post-Conditions: none
 */
int animal::getAge(){
   return age;
}
/*
 * Function: getCost()
 * Description: return animal's cost
 * Parameters: none
 * Pre-Conditions: animal is initialized
 * Post-Conditions: none
 */
int animal::getCost(){
   return cost;
}
/*
 * Function: getNumBabies()
 * Description: return animal's numBabies
 * Parameters: none
 * Pre-Conditions: animal is initialized
 * Post-Conditions: none
 */
int animal::getNumBabies(){
   return numBabies;
}
/*
 * Function: getFoodPrice()
 * Description: return animal's foodCost
 * Parameters: none
 * Pre-Conditions: animal is initialized
 * Post-Conditions: none
 */
int animal::getFoodPrice(){
   return foodCost;
}
/*
 * Function: setAge()
 * Description: set animal's age
 * Parameters: int
 * Pre-Conditions: animal is initialized
 * Post-Conditions: animal has a new age
 */
void animal::setAge(int a){
   age = a;
}
/*
 * Function: setCost()
 * Description: set animal's cost
 * Parameters: int
 * Pre-Conditions: animal is initialized
 * Post-Conditions: animal has a new cost
 */
void animal::setCost(int c){
   cost = c;
}
/*
 * Function: setNumBabies()
 * Description: set animal's numBabies
 * Parameters: int
 * Pre-Conditions: animal is initialized
 * Post-Conditions: animal has a new numBabies
 */
void animal::setNumBabies(int b){
   numBabies = b;
}
/*
 * Function: setFoodPrice()
 * Description: set animal's foodCost
 * Parameters: int
 * Pre-Conditions: animal is initialized
 * Post-Conditions: animal has a new foodCost
 */
void animal::setFoodPrice(int f){
   foodCost = f;
}
