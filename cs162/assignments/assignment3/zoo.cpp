#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include "zoo.h"
//constructor
zoo::zoo(){
   funds = 100000;
   numTigers = 0;
   numBears = 0;
   numPenguins = 0;
   tigers = new tiger[0];
   pBears = new pBear[0];
   penguins = new penguin[0];
}
//deconstructor
zoo::~zoo(){
   delete [] tigers;
   delete [] pBears;
   delete [] penguins;
}
/*
 * Function: getFunds()
 * Description: get zoo's funds
 * Parameters: none
 * Pre-Conditions: zoo is initialized
 * Post-Conditions: none
 */
int zoo::getFunds(){
   return funds;
}
/*
 * Function: getNumTigers()
 * Description: get number of tigers
 * Parameters: none
 * Pre-Conditions: zoo is initialized
 * Post-Conditions: none
 */
int zoo::getNumTigers(){
   return numTigers;
}
/*
 * Function: getNumBears()
 * Description: get number of polar bears
 * Parameters: none
 * Pre-Conditions: zoo is initialized
 * Post-Conditions: none
 */
int zoo::getNumBears(){
   return numBears;
}
/*
 * Function: getNumPenguins()
 * Description: get number of penguins
 * Parameters: none
 * Pre-Conditions: zoo is initialized
 * Post-Conditions: none
 */
int zoo::getNumPenguins(){
   return numPenguins;
}
/*
 * Function: changeMoney()
 * Description: spend/gain money
 * Parameters: int
 * Pre-Conditions: zoo is initialized
 * Post-Conditions: funds has been changed
 */
void zoo::changeMoney(int cash){
   funds += cash;
}
/*
 * Function: buyAnimal()j
 * Description: get an animal to buy from the user, update the selected animal array, subtract money from funds
 * Parameters: none
 * Pre-Conditions: zoo has been initialized
 * Post-Conditions: selected animal type has been added to specific array
 */
void zoo::buyAnimal(){
   char type;
   cout<<"You have $"<<getFunds()<<endl;
   cout<<"What kind of animal would you like to buy? Tiger (t), Polar Bear (b), penguin (p):"<<endl;
   cin>>type;
   switch(type){
      case 't':
	 //if player already has at least one tiger
	 if(numTigers > 0){
	    //create a temp array
	    tiger* temp = new tiger[numTigers];
	    //fill temp
            for(int i = 0; i < numTigers; i++)
               temp[i] = tigers[i];
	    //free tigers
	    delete [] tigers;
	    //new memory for tigers
	    tigers = new tiger[numTigers+1];
	    //copy from temp
	    for(int i = 0; i < numTigers; i++)
	       tigers[i] = temp[i];
	    //free temp
	    delete [] temp;
            //set new tiger's age to 3
	    tigers[numTigers].setAge(3);
	    //subtract cost of tiger
	    funds -= tigers[numTigers].getCost();
	    cout<<"You have $"<<getFunds()<<endl;
	    //increment numTigers
	    numTigers++;
	 }
	 //if player has no tigers
	 else{
            //free tigers
	    delete [] tigers;
            //bigger tigers
	    tigers = new tiger[numTigers+1];
	    //set new tiger's age to 3
	    tigers[numTigers].setAge(3);
	    //subtract cost of tiger
	    funds -= tigers[numTigers].getCost();
	    cout<<"You have $"<<getFunds()<<endl;
	    //increment numTigers
	    numTigers++;
	 }
	 break;
      case 'b':
	 //if player already has at least one polar bear
	 if(numBears > 0){
	    //create a temp array
	    pBear* temp = new pBear[numBears];
	    //fill temp
            for(int i = 0; i < numBears; i++)
               temp[i] = pBears[i];
	    //free pBears
	    delete [] pBears;
	    //new memory for pBears
	    pBears = new pBear[numBears+1];
	    //copy from temp
	    for(int i = 0; i < numBears; i++)
	       pBears[i] = temp[i];
	    //free temp
	    delete [] temp;
            //set new polar bear's age to 3
	    pBears[numBears].setAge(3);
	    //subtract cost of polar bear
	    funds -= pBears[numBears].getCost();
	    cout<<"You have $"<<getFunds()<<endl;
	    //increment numBears
	    numBears++;
	 }
	 //if player has no polar bears
	 else{
            //free pBears
	    delete [] pBears;
            //bigger pBears
	    pBears = new pBear[numBears+1];
	    //set new polar bear's age to 3
	    pBears[numBears].setAge(3);
	    //subtract cost of polar bear
	    funds -= pBears[numBears].getCost();
	    cout<<"You have $"<<getFunds()<<endl;
	    //increment numBears
	    numBears++;
	 }
	 break;
      case 'p':
	 //if player already has at least one penguin
	 if(numPenguins > 0){
	    //create a temp array
	    penguin* temp = new penguin[numPenguins];
	    //fill temp
            for(int i = 0; i < numPenguins; i++)
               temp[i] = penguins[i];
	    //free penguins
	    delete [] penguins;
	    //new memory for penguins
	    penguins = new penguin[numPenguins+1];
	    //copy from temp
	    for(int i = 0; i < numPenguins; i++)
	       penguins[i] = temp[i];
	    //free temp
	    delete [] temp;
            //set new penguin's age to 3
	    penguins[numPenguins].setAge(3);
	    //subtract cost of penguin
	    funds -= penguins[numPenguins].getCost();
	    cout<<"You have $"<<getFunds()<<endl;
	    //increment numPenguins
	    numPenguins++;
	 }
	 //if player has no penguins
	 else{
            //free penguins
	    delete [] penguins;
            //bigger penguins
	    penguins = new penguin[numPenguins+1];
	    //set new penguin's age to 3
	    penguins[numPenguins].setAge(3);
	    //subtract cost of penguin
	    funds -= penguins[numPenguins].getCost();
	    cout<<"You have $"<<getFunds()<<endl;
	    //increment numPenguins
	    numPenguins++;
	 }
	 break;
   }
}
/*
 * Function: death()
 * Description: select a random animal type, select a random element of that array, remove it
 * Parameters: none
 * Pre-Conditions: zoo is initialized and array has an animal
 * Post-Conditions: animal has been removed from the array
 */
void zoo::death(){
   srand(time(NULL)*2);
   int dead, animal = rand() % 3;//randomly decides what kind of animal died
   switch(animal){
      case 0://tiger
      {
	 cout<<"Oh no, a tiger got sick and died!"<<endl;
	 srand(time(NULL)*3);
         dead = rand() % numTigers;
	 //randomly kills a tiger
	 if(tigers[dead].getAge() >= 3)
	    funds -= tigers[dead].getCost();
	 else
	    funds -= 2 * tigers[dead].getCost();
	 //create a temp storage array
	 tiger* temp = new tiger[numTigers-1];
	 for(int i = 0; i < numTigers-1; i++){
	    if(i != dead)
	       temp[i] = tigers[i];
	    else//if dead location, skip it
	       continue;
	 }
	 //free memory
	 delete [] tigers;
	 //smaller tigers
	 tigers = new tiger[numTigers-1];
	 for(int i = 0; i < numTigers-1; i++)
	    tigers[i] = temp[i];
	 delete [] temp;
	 break;
      }	     
      case 1:
      {
	 cout<<"Oh no, a polar bear got sick and died!"<<endl;
	 srand(time(NULL)*3);
         dead = rand() % numBears;
	 //randomly kills a polar bear
	 if(pBears[dead].getAge() >= 3)
	    funds -= pBears[dead].getCost();
	 else
	    funds -= 2 * pBears[dead].getCost();
	 //create a temp storage array
	 pBear* temp = new pBear[numBears-1];
	 for(int i = 0; i < numBears-1; i++){
	    if(i != dead)
	       temp[i] = pBears[i];
	    else//if dead location, skip it
	       continue;
	 }
	 //free memory
	 delete [] pBears;
	 //smaller pBears
	 pBears = new pBear[numBears-1];
	 for(int i = 0; i < numBears-1; i++)
	    pBears[i] = temp[i];
	 delete [] temp;
	 break;
      }
      case 2:
      {
	 cout<<"Oh no, a penguin got sick and died!"<<endl;
	 srand(time(NULL)*3);
         dead = rand() % numPenguins;
	 //randomly kills a penguin
	 if(penguins[dead].getAge() >= 3)
	    funds -= penguins[dead].getCost();
	 else
	    funds -= 2 * penguins[dead].getCost();
	 //create a temp storage array
	 penguin* temp = new penguin[numPenguins-1];
	 for(int i = 0; i < numPenguins-1; i++){
	    if(i != dead)
	       temp[i] = penguins[i];
	    else//if dead location, skip it
	       continue;
	 }
	 //free memory
	 delete [] penguins;
	 //smaller penguins
	 penguins = new penguin[numPenguins-1];
	 for(int i = 0; i < numPenguins-1; i++)
	    penguins[i] = temp[i];
	 delete [] temp;
	 break;
      }
   }
}
/*
 * Function: bonus()
 * Description: add extra money for each tiger
 * Parameters: none
 * Pre-Conditions: zoo has been initialized
 * Post-Conditions: bonus cash
 */
void zoo::bonus(){
   cout<<"Business is booming! People love the tigers!"<<endl;
   for(int i = 0; i < numTigers; i++)
      if(tigers[i].getAge() >= 3)
	 funds += 250;
      else
	 funds += 500;
}
/*
 * Function: birth()
 * Description: select random animal to get more of, increment each array by numBabies, get some new animals
 * Parameters: none
 * Pre-Conditions: zoo is initialized, there are parents of the proper age
 * Post-Conditions: babies
 */
void zoo::birth(){
   srand(time(NULL)*2);
   int type = rand() % 3;
   switch(type){
      case 0:
      {
         bool okay = false;
	 int count = 0;
	 for(int i = 0; i < numTigers; i++){
            if(tigers[i].getAge() >= 3)
	       count++;
	    if(count = 2){
	       okay = true;
	    }
	 }
	 if(okay){
	    cout<<"It's a joyous day! A baby tiger has been born!"<<endl;
	    //create a temp array
	    tiger* temp = new tiger[numTigers];
	    //fill temp
            for(int i = 0; i < numTigers; i++)
               temp[i] = tigers[i];
	    //free tigers
	    delete [] tigers;
	    //new memory for tigers
	    tigers = new tiger[numTigers+1];
	    //copy from temp
	    for(int i = 0; i < numTigers; i++)
	       tigers[i] = temp[i];
	    //free temp
	    delete [] temp;
	    //increment numTigers
	    numTigers++;
	 }
	 else
	    cout<<"Nothing interesting happened today."<<endl;
	 break;
      }
      case 1:
      {
         bool okay = false;
	 int count = 0;
	 for(int i = 0; i < numBears; i++){
            if(pBears[i].getAge() >= 3)
	       count++;
	    if(count = 2){
	       okay = true;
	       //break;
	    }
	 }
	 if(okay){
	    cout<<"It's a wonderful day! Two baby polar bears have been born!"<<endl;
	    //create a temp array
	    pBear* temp = new pBear[numBears];
	    //fill temp
            for(int i = 0; i < numBears; i++)
               temp[i] = pBears[i];
	    //free pBear
	    delete [] pBears;
	    //new memory for pBears
	    pBears = new pBear[numBears+2];
	    //copy from temp
	    for(int i = 0; i < numBears; i++)
	       pBears[i] = temp[i];
	    //free temp
	    delete [] temp;
	    //increment numBears
	    numBears += 2;
	 }
	 else
	    cout<<"Nothing interesting happened today."<<endl;
         break;
      }
      case 2:
      {
         bool okay = false;
	 int count = 0;
	 for(int i = 0; i < numPenguins; i++){
            if(penguins[i].getAge() >= 3)
	       count++;
	    if(count = 2){
	       okay = true;
	       //break;
	    }
	 }
	 if(okay){
	    cout<<"It's a glorious day! Three baby penguins have hatched!"<<endl;
	    //create a temp array
	    penguin* temp = new penguin[numPenguins];
	    //fill temp
            for(int i = 0; i < numPenguins; i++)
               temp[i] = penguins[i];
	    //free penguins
	    delete [] penguins;
	    //new memory for penguins
	    penguins = new penguin[numPenguins+3];
	    //copy from temp
	    for(int i = 0; i < numPenguins; i++)
	       penguins[i] = temp[i];
	    //free temp
	    delete [] temp;
	    //increment numPenguins
	    numPenguins += 3;
	 }
	 else
	    cout<<"Nothing interesting happened today."<<endl;
         break;
      }
   }
}
/*
 * Function: randomEvent()
 * Description: select a random event to happen that day
 * Parameters: none
 * Pre-Conditions: zoo is initialized
 * Post-Conditions: random event has happened
 */
void zoo::randomEvent(){
   srand(time(NULL));
   int event = rand() % 4;
   switch(event){
      case 0:
	 death();
	 break;
      case 1:
	 bonus();
	 break;
      case 2:
	 birth();
	 break;
      case 3:
	 cout<<"Nothing interesting happened today."<<endl;
         break;
   }
}
/*
 * Function: activateDay()
 * Description: play one game round: increment ages, subtract funds, do a random event, maybe buy an animal, get some money back
 * Parameters: none
 * Pre-Conditions: zoo is properly initialized
 * Post-Conditions: one day has been played
 */
 void zoo::activateDay(){
   int ya;
   cout<<"At the start of the day you have $"<<getFunds()<<endl;
   for(int t = 0; t < numTigers; t++){
      tigers[t].setAge(tigers->getAge()+1);
      funds -= tigers[t].getFoodPrice();
   }
   for(int b = 0; b < numBears; b++){
      pBears[b].setAge(pBears->getAge()+1);
      funds -= pBears[b].getFoodPrice();
   }
   for(int p = 0; p < numPenguins; p++){
      penguins[p].setAge(penguins->getAge()+1);
      funds -= penguins[p].getFoodPrice();
   }
   cout<<"After feeding you have $"<<getFunds()<<endl;
   randomEvent();
   cout<<"Would you like to buy a new animal? 1 = yes, 0 = no:"<<endl;
   cin>>ya;
   if(ya)
      buyAnimal();
   for(int t = 0; t < numTigers; t++)
      if(tigers[t].getAge() >= 3)
         funds += 0.1*tigers[t].getCost();
      else
	 funds += (0.1*tigers[t].getCost())*2;
   for(int b = 0; b < numBears; b++)
      if(pBears[b].getAge() >= 3)
	 funds += (0.05*pBears[b].getCost());
      else
	 funds += (0.05*pBears[b].getCost())*2;
   for(int p = 0; p < numPenguins; p++)
      if(penguins[p].getAge() >= 3)
	 funds += (0.05*penguins[p].getCost());
      else
	 funds += (0.05*penguins[p].getCost())*2;
   cout<<"At the end of the day you have $"<<getFunds()<<endl;
}
/*
 * Function: playGame()
 * Description: play the game until player is done
 * Parameters: none
 * Pre-Conditions: zoo has been initialized
 * Post-Conditions: player is happy
 */
void zoo::playGame(){
   int buy, can = 0, cont = 1;
   while(can < 6){
      cout<<"You have $"<<getFunds()<<", "<<getNumTigers()<<" tigers, "<<getNumBears()<<" polar bears, and "<<getNumPenguins()<<" penguins. Would you like to buy any more animals? 1 = yes, 0 = no."<<endl;
      cin>>buy;
      if(buy){
	 buyAnimal();
	 can++;
      }
      else
	 break;
   }
   while(cont){
      activateDay();
      cout<<"Move on to next day? 1 = continue, 0 = end game:"<<endl;
      cin>>cont;
      if(cont)
	 continue;
      else{
	 cout<<"You ended the game with $"<<getFunds()<<", "<<getNumTigers()<<" tigers, "<<getNumBears()<<" polar bears, and "<<getNumPenguins()<<" penguins!"<<endl;
	 break;
      }
   }
}
