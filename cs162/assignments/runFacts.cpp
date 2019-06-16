/* Program: runFacts.cpp
 * Author: Ryan Howerton
 * Date: 4/10/2016
 * Description: Reads information about states and their counties from a .txt file and interprets the data
 * Input: Expected number of states and file name
 * Output: The largest state, the Largest county, the counties with average income above a specified number, average cost of a house, then the states and counties sorted by name and population.
 */ 
#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;
#include "stateFacts.h"

int main(int argc, char* argv[]){
   int numStates, income, cont = 1;
   while(cont == 1){
      bool okay = isValidArguments(argc, argv);//proper num args and proper commands.
      if(!okay)
         return 0;
      while(!isdigit(*argv[2])){//valid number of states.
         cout<<"Invalid number of states. Enter positive number between 0 and 50:"<<endl;
         cin>>argv[2];
      }

      ifstream input;
      input.open(argv[4]);
      while(input.fail()){//available text file
         cout<<"Invalid filename. Enter proper filename:"<<endl;
         cin>>argv[4];
         input.open(argv[4]);
      }

      getNumStates(argc, argv, &numStates);//gets number of states from c-line
      state* states = createStates(numStates);//creates array of states
      getStateData(numStates, states, input);//gets state data from .txt file
      largestState(states, numStates);//prints name of largest state
      largestCounty(states, numStates);//prints name of largest county
      cout<<"Enter average income to check:"<<endl; cin>>income;//income to check against
      richCounties(states, numStates, income);//prints counties above income
      averageHouseCost(states, numStates);//prints average cost of houses
      sortCountyNames(states, numStates);//sorts counties by name and prints list
      sortCountyPopulation(states, numStates);//sorts counties by population and prints
      sortStateNames(states, numStates);//sorts states by name and prints list
      sortStatePopulation(states, numStates);//sorts states by population and prints list
      input.close();//closes file
      deleteInfo(states, numStates);//deletes all arrays
      cout<<"Continue? 1 = yes, 0 = no:"<<endl; cin>>cont;//asks if user wants to continue
      if(cont == 0)
	 break;
      else{//gets new info
	 cout<<"New file to read:"<<endl; cin>>argv[4];
	 cout<<"New number of states:"<<endl; cin>>argv[2];
      }
   }
   return 0;
}
