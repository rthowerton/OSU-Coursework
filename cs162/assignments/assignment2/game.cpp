#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include "card.h"
#include "hand.h"
#include "player.h"
#include "dealer.h"
#include "game.h"
//default constructor
game::game(){
   players = new player[0];
   numPlayers = 0;
}
//non-default constructor
game::game(int num){
   numPlayers = num;
   players = new player[num];
}
//destructor
game::~game(){
   delete [] players;
}
/*
 * Function: getNumPlayers
 * Description: return numPlayers
 * Parameters: none
 * Pre-Conditions: numPlayers has been initialized
 * Post-Conditions: none
 */
int game::getNumPlayers(){
   return numPlayers;
}
/*
 * Function: setPlayers
 * Description: sets array of players to a new size
 * Parameters: int
 * Pre-Conditions: players has been initialized
 * Post-Conditions: players has a new size, numPlayers
 */
void game::setPlayers(int newNum){
   for(int i = 0; i < numPlayers; i++)
      delete &players[i];
   players = new player[newNum];
   numPlayers = newNum;
}
/*
 * Function: playGame
 * Description: sets up the deck, dealer, and players with their respective hands, then proceeds to call all the functions related to the game
 * Parameters: none
 * Pre-Conditions: everything has been initialized to base values
 * Post-Conditions: fun has been had and money has been lost
 */
void game::playGame(){
   bool cont = 1, hit = 1; int cash;
   for(int i = 0; i < numPlayers; i++){
      cout<<"Enter player "<<i+1<<"'s initial money pool:"<<endl;
      cin>>cash;
      players[i].changePlayerMoney(cash);
   }
   //start game
   while(cont){
      //shuffle deck
      theDeck.shuffleDeck();
      //deal 2 cards to all players
      for(int i = 0; i < numPlayers; i++){
	 for(int j = 0; j < 2; j++){
	    theDeck.dealCard(players[i].getPlayerHand(), theDeck.getNextCard());
	    players[i].addCardTotal(theDeck.getCurrentCard().getValue());
	 }
      }
      //deal 2 cards to dealer
      for(int i = 0; i < 2; i++){
         theDeck.dealCard(house.getDealerHand(), theDeck.getNextCard());
         house.addCardTotal(theDeck.getCurrentCard().getValue());
      }
      //each player places a bet
      for(int i = 0; i < numPlayers; i++){
	 cout<<"Player "<<i+1<<", you have "<<players[i].getPlayerMoney()<<" dollars. How much would you like to bet?"<<endl;
         cin>>cash;
	 while(cash < 0 || cash > players[i].getPlayerMoney()){
	    cout<<"Invalid amount to bet."<<endl;
	    cout<<"Player "<<i+1<<", you have "<<players[i].getPlayerMoney()<<" dollars. How much would you like to bet?"<<endl;
            cin>>cash;
	 }
	 players[i].addBet(cash);
      }
      //each player chooses whether to hit or stay
      for(int i = 0; i < numPlayers; i++){
	 cout<<"Player "<<i+1<<" card total: "<<players[i].getCardTotal()<<endl;
         cout<<"Player "<<i+1<<", Hit(1) or Stay(0)?"<<endl;
	 cin>>hit;
	 while(hit){
            theDeck.dealCard(players[i].getPlayerHand(), theDeck.getNextCard());
	    players[i].addCardTotal(theDeck.getCurrentCard().getValue());
	    if(players[i].getCardTotal() > 21){
	       cout<<"Player "<<i+1<<" card total: "<<players[i].getCardTotal()<<endl;
	       cout<<"Bust!"<<endl;
	       break;
	    }
	    cout<<"Player "<<i+1<<" card total: "<<players[i].getCardTotal()<<endl;
            cout<<"Player "<<i+1<<", Hit(1) or Stay(0)?"<<endl;
	    cin>>hit;
	 }
      }
      //dealer goes until cardTotal >= 16
      while(house.getCardTotal() < 16){
	 cout<<"Dealer card total: "<<house.getCardTotal()<<endl;
	 theDeck.dealCard(house.getDealerHand(), theDeck.getNextCard());
	 house.addCardTotal(theDeck.getCurrentCard().getValue());
      }
      //check each player cardTotal vs dealer cardTotal
      for(int i = 0; i < numPlayers; i++){
	 //check for player bust
	 if(players[i].getCardTotal() > 21){
	    cout<<"Player "<<i+1<<" busted!"<<endl;
	    players[i].changePlayerMoney((-1)*players[i].getBet());
	 }
	 //if dealer busted
	 if(house.getCardTotal() > 21){
	    cout<<"Dealer busted!"<<endl;
	    if(players[i].getCardTotal() < 21){
	       cout<<"Player "<<i+1<<" got "<<players[i].getCardTotal()<<"!"<<endl;
	       players[i].changePlayerMoney(players[i].getBet());
	    }
	    //and player got 21
	    else if(players[i].getCardTotal() == 21){
	       cout<<"Player "<<i+1<<" got 21!"<<endl;
	       players[i].changePlayerMoney((players[i].getBet())*1.5);
	    }
	 }
	 //dealer did not bust
         else{
	    //if player got less than 21 but greater than dealer
	    cout<<"Dealer has "<<house.getCardTotal()<<"."<<endl;
	    if(players[i].getCardTotal() < 21 && players[i].getCardTotal() > house.getCardTotal()){
	       cout<<"Player "<<i+1<<" got "<<players[i].getCardTotal()<<"!"<<endl;
	       players[i].changePlayerMoney(players[i].getBet());
	    }
	    //if player got 21
            else if(players[i].getCardTotal() == 21){
	       cout<<"Player "<<i+1<<" got 21!"<<endl;
	       players[i].changePlayerMoney((players[i].getBet())*1.5);
	    }
	    //if player got same as dealer
	    else if(players[i].getCardTotal() == house.getCardTotal())
	       cout<<"Player "<<i+1<<" got the same as dealer."<<endl;
	 }
      }
      //reset players hands
      for(int i = 0; i < numPlayers; i++){
	 players[i].getPlayerHand().resetHand();
	 players[i].resetCardTotal();
      }
      //reset dealer hand
      house.getDealerHand().resetHand();
      house.resetCardTotal();
      theDeck.resetCurrentCard();
      //tell each player how much money they have
      for(int i = 0; i < numPlayers; i++)
         cout<<"Player "<<i<<", you have "<<players[i].getPlayerMoney()<<" dollars left. "<<endl;
      //ask for continue
      cout<<"Another round? 1 = continue, 0 = stop."<<endl;
      cin>>cont;
   }
   cout<<"Have a nice day!"<<endl;;
}
