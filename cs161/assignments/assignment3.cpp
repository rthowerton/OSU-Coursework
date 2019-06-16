/*******************************************************************************************
 * Program: Assignment3.cpp
 * Author: Ryan Howerton
 * Date: 1/31/16
 * Description: Practice in error handling and embedded for loops in a simplistic rover test.
 * Input: none
 * Output: 4x4 grid with a moving X.
 *******************************************************************************************/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void print_grid(int xPos, int yPos);
void find_path(int xStart, int yStart, int xEnd, int yEnd);
/******************************************************************************************
 * Function: main()
 * Description: Take user input and check for errors. Pass user input to other functions.
 * Parameters: None.
 * Pre-Conditions: User input taken as strings.
 * Post-Conditions: User input converted to integers between 0 and 3 inclusive.
 ******************************************************************************************/
int main(){
   int cont = 1;
   while(cont == 1){
      string sx1, sx2, sy1, sy2;
      int ix1, ix2, iy1, iy2;
      cout<<"Rover's initial X position (between 0 and 3): ";
      cin>>sx1;
      while(true){
	 for(int i = 0; i < sx1.length(); i++){
	    if(!(sx1.at(i) >= '0' && sx1.at(i) <= '3')){
	       cout<<"Invalid input."<<endl;
	       cout<<"Rover's initial X position (between 0 and 3): ";
	       cin>>sx1;
	       i--;
	    }
	 }
	 break;
      }
      ix1 = atoi(sx1.c_str());
      cout<<"Rover's initial Y position (between 0 and 3): ";
      cin>>sy1;
      while(true){
	 for(int i = 0; i < sy1.length(); i++){
	    if(!(sy1.at(i) >= '0' && sy1.at(i) <= '3')){
	       cout<<"Invalid input."<<endl;
	       cout<<"Rover's initial Y position (between 0 and 3): ";
	       cin>>sy1;
	       i--;
	    }
	 }
	 break;
      }
      iy1 = atoi(sy1.c_str());
      cout<<"Rover's final X position (between 0 and 3): ";
      cin>>sx2;
      while(true){
	 for(int i = 0; i < sx2.length(); i++){
	    if(!(sx2.at(i) >= '0' && sx2.at(i) <= '3')){
	       cout<<"Invalid input."<<endl;
	       cout<<"Rover's final X position (between 0 and 3): ";
	       cin>>sx2;
	       i--;
	    }
	 }
	 break;
      }
      ix2 = atoi(sx2.c_str());
      cout<<"Rover's final Y position (between 0 and 3): ";
      cin>>sy2;
      while(true){
	 for(int i = 0; i < sy2.length(); i++){
	    if(!(sy2.at(i) >= '0' && sy2.at(i) <= '3')){
	       cout<<"Invalid input."<<endl;
	       cout<<"Rover's final Y position (between 0 and 3): ";
	       cin>>sy2;
	       i--;
	    }
	 }
	 break;
      }
      iy2 = atoi(sy2.c_str());
      print_grid(ix1, iy1);
      find_path(ix1, iy1, ix2, iy2);

      cout<<"Continue? 1 = yes, 0 = no: ";
      cin>>cont;
   }
   return 0;
}
/*************************************************************************************
 * Function: print_grid(int xPos, int yPos)
 * Description: Prints a grid of boxes with an X marking rover's location.
 * Parameters: 2 integers, xPos and yPos.
 * Pre-Conditions: Parameters are integers between 0 and 3 inclusive.
 * Post-Conditions: Prints grid with rover's current location marked.
 *************************************************************************************/
void print_grid(int xPos, int yPos){
   for(int i = 3; i >= 0; i--){
      for(int j = 0; j < 4; j++){
	 if(i == yPos && j == xPos)
	    cout<<"[X]";
	 else
	    cout<<"[ ]";
      }
      cout<<endl;
   }
   cout<<"------------"<<endl;
}
/*************************************************************************************
 * Function: find_path(int xStart, int yStart, int xEnd, int yEnd)
 * Description: Takes rover starting position and prints a path to the end position.
 * Parameters: 4 integers, xStart, yStart, xEnd, and yEnd.
 * Pre-Conditions: Parameters are intevers between 0 and 3 inclusive.
 * Post-Conditions: Passes print_grid 2 integer values between 0 and 3 inclusive.
 *************************************************************************************/
void find_path(int xStart, int yStart, int xEnd, int yEnd){
   int x = xStart;
   int y = yStart;
   for(int i = 0; i < 4; i++){
      if(y > yEnd){
	 y--;
	 print_grid(x, y);
      }
      else if(y < yEnd){
	 y++;
	 print_grid(x, y);
      }
      else
	 continue;
   }
   for(int j = 0; j < 4; j++){
      if(x > xEnd){
	 x--;
	 print_grid(x, y);
      }
      else if(x < xEnd){
	 x++;
	 print_grid(x, y);
      }
      else
	 continue;
   }
}
