#include <iostream>
using namespace std;
#include "card.h"
//default constructor
card::card(){
   value = 0;
   suit = spades;
}
//deconstructor
card::~card(){
}
//assignment operator overload definition
void card::operator=(const card& c){
   value = c.value;
   suit = c.suit;
}
/*
 * Function: getValue
 * Description: return card value
 * Paramters: none
 * Pre-conditions: card has value
 * Post-conditions: none
 */
int card::getValue(){
   return value;
}
/*
 * Function: getSuit
 * Description: return card suit
 * Parameters: none
 * Pre-Conditions: card has suit
 * Post-Conditions: none
 */
cardSuit card::getSuit(){
   return suit;
}
/*
 * Function: setValue
 * Description: set card's value to a number
 * Parameters: int
 * Pre-Conditions: card is initialized
 * Post-Conditions: card has a new value
 */
void card::setValue(int v){
   if(v <= 10)
      value = v;
   else
      value = 10;
}
/*
 * Function: setSuit
 * Description: set card's suit to a cardSuit
 * Parameters: cardSuit
 * Pre-Conditions: card is initialized
 * Post-Conditions: card has a new suit
 */
void card::setSuit(cardSuit s){
   suit = s;
}
