#include <iostream>
using namespace std;
#include "card.h"
#include "hand.h"
#include "dealer.h"
//default constructor
dealer::dealer(){
   cardTotal = 0;
}
//deconstructor
dealer::~dealer(){
   delete [] dHand.getCardsList();
}
/*
 * Function: getDealerHand
 * Description: access the dealer's hand
 * Parameters: none
 * Pre-Conditions: hand is initialized
 * Post-Conditions: none
 */
hand dealer::getDealerHand(){
   return dHand;
}
/*
 * Function: getCardTotal
 * Description: access dealer's cardTotal
 * Parameters: none
 * Pre-Conditions: cardTotal is initialized
 * Post-Conditions: none
 */
int dealer::getCardTotal(){
   return cardTotal;
}
/*
 * Function: addCardTotal
 * Description: add a card's value to the dealer's total
 * Parameters: int
 * Pre-Conditions: cardTotal is initialized
 * Post-Conditions: value has been added to card total
 */
void dealer::addCardTotal(int value){
   cardTotal += value;
}
/*
 * Function: resetCardTotal
 * Description: reset dealer's card total to 0
 * Parameters: none
 * Pre-Conditions: cardTotal is initialized
 * Post-Conditions: cardTotal is 0
 */
void dealer::resetCardTotal(){
   cardTotal = 0;
}
