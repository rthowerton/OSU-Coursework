#include <iostream>
#include <stdlib.h>
using namespace std;
#include "cave.h"

int checkArgs(int numArgs, char** args, int* length){
   cout<<numArgs<<endl;
   cout<<args[1][0]<<endl;
   if(numArgs != 2 || args[1][0] < '4')
      return 1;
   else{
      *length = atoi(args[1]);
      return 0;
   }
}

int main(int argc, char* argv[]){
   char moveShoot;
   int length, again = 1;
   int check = checkArgs(argc, argv, &length);
   cout<<length<<endl;
   if(check == 1){
      cout<<"Incorrect initializing values."<<endl;
      return 1;
   }
   else{
      cave c(length, length);
      c.allocateStuff();
      c.placePlayer();
      while(again != 0){
         while(c.playerLives() == true && c.winCondition() == false){
            c.drawCave();
            c.callPercepts();
            cout<<"Move (m) or shoot (s)?"<<endl;
            cin>>moveShoot;
            switch(moveShoot){
	       case 'M':
	       case 'm':
	          c.movePlayer();
	          break;
	       case 'S':
	       case 's':
	          c.shootArrow();
	          break;
            }
         }
         if(c.playerLives() == false){
            cout<<"Git gud, kid."<<endl;
            cout<<"Would you like to play again with the same configuration (2) {currently unavailable}, with a new configuration (1), or quit (0)?"<<endl;
	    cin>>again;
	    switch(again){
	       case 0:
	          break;
	       case 1:
	          main(argc, argv);
	          break;
	    }
	 }
         else{
	    again = 0;
            cout<<"Not bad."<<endl;
         }
      }
   }
}
