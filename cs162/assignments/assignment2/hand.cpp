#include <iostream>
#include <time.h>
using namespace std;
#include "card.h"
#include "hand.h"
//default constructor
hand::hand(){
   cards = new card[11];//initialize cards to size 11
   for(int i = 0; i < 11; i++){
      cards[i].setValue(0);//set a neutral value of 0
      cards[i].setSuit(cardSuit(0));//set suit to spades
   }
   numCards = 0;//no cards in hand
}
//deconstructor
hand::~hand(){
}
/*
 * Function: setCards
 * Description: set the cards array to a new size
 * Parameters: int
 * Pre-Conditions: cards is initialized
 * Post-Conditions: cards has new size
 */
void hand::setCards(int i){
   cards = new card[i];
   numCards = i;
}
/*
 * Function: addCard
 * Description: add a card to the hand
 * Parameters: card
 * Pre-Conditions: there is empty space in the hand
 * Post-Conditions: card passed is added to hand
 */
void hand::addCard(card c){
   for(int i = 0; i < 11; i++){//for max hand size, check each location
      if(cards[i].getValue() == 0){//if location is neutral
	 cards[i].setValue(c.getValue());//set location value to c.getValue()
	 cards[i].setSuit(c.getSuit());//set location suit to c.getSuit()
         break;
      }
   }
   numCards++;//increment numCards
}
/*
 * Function: getCardsList
 * Description: return array of cards
 * Parameters: none
 * Pre-Conditions: cards is initialized
 * Post-Conditions: none
 */
card* hand::getCardsList() {
   return cards;
}
/*
 * Function: getNumCards
 * Description: return numCards
 * Parameters: none
 * Pre-Conditions: hand is initialized
 * Post-Conditions: none
 */
int hand::getNumCards(){
   return numCards;
}
/*
 * Function: resetHand
 * Description: reset array cards to 0 values
 * Parameters: none
 * Pre-Conditions: cards is initialized
 * Post-Conditions: every part of cards is zeroed
 */
void hand::resetHand(){
   for(int i = 0; i < 11; i++){
      cards[i].setValue(0);
      cards[i].setSuit(cardSuit(0));
   }
   numCards = 0;
}
