#include <iostream>
using namespace std;
#include "card.h"
#include "hand.h"
#include "player.h"
//default constructor
player::player(){
   playerMoney = 0;//player's money is 0
   cardTotal = 0;//player's card total is 0
   bet = 0;//player's bet is 0
}
//deconstructor
player::~player(){
   delete [] pHand.getCardsList();
}
/*
 * Function: getPlayerHand
 * Description: return pHand
 * Parameters: none
 * Pre-Conditions: pHand is initialized
 * Post-Conditions: none
 */
hand player::getPlayerHand(){
   return pHand;
}
/*
 * Function: getPlayerMoney
 * Description: return player's pool of money
 * Parameters: none
 * Pre-Conditions: playerMoney is initialized
 * Post-Conditions: none
 */
int player::getPlayerMoney(){
   return playerMoney;
}
/*
 * Function: getCardTotal
 * Description: return player's card total
 * Parameters: none
 * Pre-Conditions: cardTotal is initialized
 * Post-Conditions: none
 */
int player::getCardTotal(){
   return cardTotal;
}
/*
 * Function: getBet
 * Description: return player's bet
 * Parameters: none
 * Pre-Conditions: bet is initialized
 * Post-Conditions: none
 */
int player::getBet(){
   return bet;
}
/*
 * Function: changePlayerMoney
 * Description: add/subtract money from player's pool
 * Parameters: int
 * Pre-Conditions: playerMoney is initialized
 * Post-Conditions: playerMoney is changed
 */
void player::changePlayerMoney(int cash){
   playerMoney += cash;
}
/*
 * Function: addCardTotal
 * Description: adds a card's face value to the player's card total
 * Parameters: int
 * Pre-Conditions: cardTotal is initialized
 * Post-Conditions: cardTotal is edited
 */
void player::addCardTotal(int value){
   cardTotal += value;
}
/*
 * Function: addBet
 * Description: increase/decrease a player's bet
 * Parameters: int
 * Pre-Conditions: bet is initialized
 * Post-Conditions: bet is changed
 */
void player::addBet(int add){
   bet = add;
}
/*
 * Function: resetCardTotal
 * Description: resets a player's card total to 0
 * Parameters: none
 * Pre-Conditions: cardTotal is initialized
 * Post-Conditions: cardTotal is 0
 */
void player::resetCardTotal(){
   cardTotal = 0;
}
