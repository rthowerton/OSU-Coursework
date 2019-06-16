#include <iostream>
#include <stdlib.h>
#include <time.h>
using std::cout;
using std::endl;
using std::cin;
#include "cave.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"
#include "nothing.h"
#include "rope.h"
#include "player.h"
//default constructor
cave::cave(){
   lair = new room*[1];
   lair[0] = new room[1];
   numRows = 1;
   numCols = 1;
}
//non-default constructor
cave::cave(int x, int y){
   numRows = y;
   numCols = x;
   lair = new room*[y];
   for(int i = 0; i < y; i++){
      lair[i] = new room[x];
   }
   jeremy.numArrows = 3;
   jeremy.hasGold = false;
   hasWon = false;
}
//deconstructor
cave::~cave(){
   for(int i = 0; i < numRows; i++)
         delete [] lair[i];
   delete [] lair;
}
//allocate stuff
void cave::allocateStuff(){
   srand(time(NULL));
   int row, col;
   gold bling;
   bats bat1, bat2;
   pit pit1, pit2;
   //place wumpus
   for(int i = 0; i < 1; ){
      row = rand()%numRows, col = rand()%numCols;
      if(lair[row][col].getEvent()->getType() == ' '){
         lair[row][col].getEvent()->changeEvent(&wump);
	 isWumpus = true;
	 wump.setRow(row);
	 wump.setCol(col);
	 i++;
      }
   }
   //place gold
   for(int i = 0; i < 1; ){
      row = rand()%numRows, col = rand()%numCols;
      if(lair[row][col].getEvent()->getType() == ' '){
         lair[row][col].getEvent()->changeEvent(&bling);
	 bling.setRow(row);
	 bling.setCol(col);
	 i++;
      }
   }
   //place bats
   for(int i = 0; i < 2; ){
      row = rand()%numRows, col = rand()%numCols;
      if(i == 0 && lair[row][col].getEvent()->getType() == ' '){
         lair[row][col].getEvent()->changeEvent(&bat1);
	 i++;
      }
      else if(i == 1 && lair[row][col].getEvent()->getType() == ' '){
	 lair[row][col].getEvent()->changeEvent(&bat2);
	 i++;
      }
   }
   //place pits
   for(int i = 0; i < 2; ){
      row = rand()%numRows, col = rand()%numCols;
      if(i == 0 && lair[row][col].getEvent()->getType() == ' '){
         lair[row][col].getEvent()->changeEvent(&pit1);
	 i++;
      }
      else if(i == 1 && lair[row][col].getEvent()->getType() == ' '){
	 lair[row][col].getEvent()->changeEvent(&pit2);
	 i++;
      }
   }
}

//place player
void cave::placePlayer(){
   rope exit;
   int row, col;
   //place rope
   for(int i = 0; i < 1; ){
      row = rand()%numRows, col = rand()%numCols;
      if(lair[row][col].getEvent()->getType() == ' '){
         lair[row][col].getEvent()->changeEvent(&exit);
	 exit.setRow(row);
	 exit.setCol(col);
         jeremy.pRow = row;
         jeremy.pCol = col;
	 isPlayer = true;
	 i++;
      }
   }
}

//draw the cave
void cave::drawCave(){
   cout<<"drawing cave"<<endl;
   for(int i = 0; i < numRows; i++){
      for(int j = 0; j < numCols; j++){
	 if(jeremy.pRow == i && jeremy.pCol == j)
	    cout<<"[J]";
	 else
	    cout<<"["<<this->lair[i][j].getEvent()->getType()<<"]";
      }
      cout<<endl;
   }
}
//call surrounding percepts
void cave::callPercepts(){
   for(int i = 0; i < numRows; i++){
      for(int j = 0; j < numCols; j++){
	 if((i >= (jeremy.pRow)-1 && i <= (jeremy.pRow)+1 && j == jeremy.pCol) || (j >= (jeremy.pCol)-1 && j <= (jeremy.pCol)+1 && i == jeremy.pRow)){
	    lair[i][j].getEvent()->near();
	 }
      }
   }
}
//move player
void cave::movePlayer(){
   char move;
   cout<<"Which direction will you move? Up (w), left (a), down (s), or right (d)?"<<endl;
   cin>>move;
   switch(move){
      case 'W':
      case 'w':
      {
	 jeremy.pRow--;
         if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'p')
	    pitStop();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'b')
	    batnapping();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'g')
	    getGold();
	 else if(isWumpus == true && jeremy.pRow == wump.getRow() && jeremy.pCol == wump.getCol())
	    gitGud();
	 break;
      }
      case 'A':
      case 'a':
      {
	 jeremy.pCol--;
         if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'p')
	    pitStop();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'b')
	    batnapping();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'g')
	    getGold();
	 else if(isWumpus == true && jeremy.pRow == wump.getRow() && jeremy.pCol == wump.getCol())
	    gitGud();
	 break;
      }
      case 'S':
      case 's':
      {
	 jeremy.pRow++;
         if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'p')
	    pitStop();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'b')
	    batnapping();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'g')
	    getGold();
	 else if(isWumpus == true && jeremy.pRow == wump.getRow() && jeremy.pCol == wump.getCol())
	    gitGud();
	 break;
      }
      case 'D':
      case 'd':
      {
	 jeremy.pCol++;
         if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'p')
	    pitStop();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'b')
	    batnapping();
	 else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'g')
	    getGold();
	 else if(isWumpus == true && jeremy.pRow == wump.getRow() && jeremy.pCol == wump.getCol())
	    gitGud();
	 break;
      }
   }
}
//shoot an arrow
void cave::shootArrow(){
   srand(time(NULL));
   char fire;
   int count = 0;
   cout<<"Which direction will you fire in? Up (w), left (a), down (s), right (d)?"<<endl;
   cin>>fire;
   switch(fire){
      case 'W':
      case 'w':
      {
	 for(int y = jeremy.pRow; y > 0 || count < 3; y--){
	    if(y == wump.getRow() && jeremy.pCol == wump.getCol()){
               notBad();
               break;
	    }
	    else
	       count++;
	 }
	 if(isWumpus){
	    moveWumpus();
	 }
	 jeremy.numArrows--;
	 break;
      }
      case 'A':
      case 'a':
      {
         for(int x = jeremy.pCol; x > 0 || count < 3; x--){
	    if(x == wump.getCol() && jeremy.pRow == wump.getRow()){
	       notBad();
	       break;
	    }
	    else
	       count++;
	 }
	 if(isWumpus){
	    moveWumpus();
	 }
	 jeremy.numArrows--;
	 break;
      }
      case 'S':
      case 's':
      {
	 for(int y = jeremy.pRow; y < numRows || count < 3; y++){
	    if(y == wump.getRow() && jeremy.pCol == wump.getCol()){
	       notBad();
	       break;
	    }
	    else
	       count++;
	 }
	 if(isWumpus){
	    moveWumpus();
	 }
	 jeremy.numArrows--;
	 break;
      }
      case 'D':
      case 'd':
      {
	 for(int x = jeremy.pCol; x < numCols || count < 3; x++){
	    if(x == wump.getCol() && jeremy.pRow == wump.getRow()){
	       notBad();
	       break;
	    }
	    else
	       count++;
	 }
	 if(isWumpus){
	    moveWumpus();
	 }
	 jeremy.numArrows--;
	 break;
      }
   }
}
//kill wumpus
void cave::notBad(){
   nothing here;
   cout<<"With a terrible scream and a final gurgle, the beast falls lifeless to the ground, your feathered shaft buried deep in its heart."<<endl;
   lair[wump.getRow()][wump.getCol()].getEvent()->changeEvent(&here);
   isWumpus = false;
   cout<<isWumpus<<endl;
}
//get killed by wumpus
void cave::gitGud(){
   cout<<"As your senses get overwhelmed by the awful stench of that hooker from Frid-sorry, the monster, you stumble unwittingly into the room where it sleeps. As your foot touches the stone, its eyes snap open, and its jaws just as quickly. Then, darkness."<<endl;
   isPlayer = false;
}
//move wumpus
void cave::moveWumpus(){
   srand(time(NULL));
   nothing here;
   int moves = rand() % 4;
   if(moves > 0){
      cout<<"As your arrow clatters against the stone, the terrible wumpus opens one eye, stretches, then softly moves to a deeper, darker corner of its lair."<<endl;
      for(int i = 0; i < 1; ){
         int newRow = rand() % numRows, newCol = rand() % numCols;
	 if(lair[newRow][newCol].getEvent()->getType() == ' '){
            lair[wump.getRow()][wump.getCol()].getEvent()->changeEvent(&here);
            wump.setRow(newRow);
            wump.setCol(newCol);
            lair[wump.getRow()][wump.getCol()].getEvent()->changeEvent(&wump);
	    i++;
	 }
      }
   }
   else
      cout<<"Undeterred by the hunter in its lair, the beast blissfully snores on."<<endl;
}
//fall in pit
void cave::pitStop(){
   cout<<"As you enter the pit black room, you find your foot over empty space. Before you can save yourself, you're falling, falling, falling... with no bottom in sight."<<endl;
   isPlayer = false;
}
//spirited away
void cave::batnapping(){
   srand(time(NULL));
   int newRow = rand() % numRows, newCol = rand() % numCols;
   cout<<"With a screech and a flurry of enormous wings, super bats come streaming out of the darkness. You find yourself gripped in supernaturally strong talons, when suddenly you're in a room you don't recognize."<<endl;
   jeremy.pRow = newRow;
   jeremy.pCol = newCol;
   if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'p')
      pitStop();
   else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'b')
      batnapping();
   else if(lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'g')
      getGold();
   
}
//there's gold in them thar hills!
void cave::getGold(){
   nothing here;
   cout<<"You enter a room bathed in the warmth and luster of the sun, surrounded on all sides by piles and piles of gold and jewels. Lucky you have deep pockets."<<endl;
   jeremy.hasGold = true;
   lair[jeremy.pRow][jeremy.pCol].getEvent()->changeEvent(&here);
}
//check if player still lives
bool cave::playerLives(){
   return isPlayer;
}
//check if player has won
bool cave::winCondition(){
   if(isWumpus == false && jeremy.hasGold && lair[jeremy.pRow][jeremy.pCol].getEvent()->getType() == 'r'){
	    cout<<"You feel a breath of fresh air as you enter the next room. Your rope! You've done it! The wumpus is dead, your pockets are heavy, and your heart still pumps. 'Grats."<<endl;
      hasWon = true;
   }
   return hasWon;
}
