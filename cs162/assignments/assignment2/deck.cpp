#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include "card.h"
#include "hand.h"
#include "deck.h"
//default constructor
deck::deck(){
   int count = 0;//deck size
   for(int i = 0; i < 4; i++){//for number of suits
      for(int j = 1; j <= 13; j++){//for number of values
	 cards[count].setSuit(cardSuit(i));//set current position's suit
         cards[count].setValue(j);//set current position's value
	 count++;//increment position
      }
   }
   currentCard = 52;//set index to 52
}
//destructor
deck::~deck(){
}
/*
 * Function: shuffleDeck
 * Description: pseudo-shuffle the deck
 * Parameters: none
 * Pre-Conditions: deck is initialized
 * Post-Conditions: deck has been slightly randomized
 */
void deck::shuffleDeck(){
   srand(time(NULL));//seed pseudo-random number generator
   for(int i = 0; i < 1000; i++){//1000 replacements to shuffle
   int first = rand() % 52;//first card position
   int second = rand() % 52;//second card position
   card temp = cards[first];//placeholder gets first position
   cards[first] = cards[second];//first position gets replaced
   cards[second] = temp;//second position gets placed
   }
}
/*
 * Function: dealCard
 * Description: deal a card to a specified hand
 * Parameters: hand, card
 * Pre-Conditions: both the card and hand exist
 * Post-Conditions: card c exists in hand h
 */
void deck::dealCard(hand h, card c){
   h.addCard(c);//call addCard function from hand.h to add values of card c to h

}
/*
 * Function: getCurrentCard
 * Description: return the current card of the deck
 * Parameters: none
 * Pre-Conditions: cards is initialized and shuffled
 * Post-COnditions: none
 */
card deck::getCurrentCard(){
   return cards[currentCard];
}
/*
 * Function: getNextCard
 * Description: get the next card from the top of the deck
 * Parameters: none
 * Pre-Conditions: currentCard exists on the deck
 * Post-Conditions: next card has been returned
 */
card deck::getNextCard(){
   currentCard--;//decrease index to simulate dealing top card
   return cards[currentCard];//return members of card at index
}
/*
 * Function: resetCurrentCard
 * Description: after round has been played, reset the deck and return to top
 * Parameters: none
 * Pre-Conditions: deck has been reshuffled
 * Post-Conditions: currentCard has been reset
 */
void deck::resetCurrentCard(){
   currentCard = 52;
}
