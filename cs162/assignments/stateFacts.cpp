#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
using namespace std;
#include "stateFacts.h"

/* 
 * Function: isValidArguments
 * Description: Checks if user provided valid c-line args. This includes correct number and denotators.
 * Parameters: int, char**
 * Pre-Conditions: none
 * Post-Conditions: returns false if numArgs != 5 or the denotators are not -s or -f
 */
bool isValidArguments(int numArgs, char* info[]){
   if(numArgs != 5){
      cout<<"Invalid number of arguments."<<endl;
      return false;
   }
   for(int i = 0; i < numArgs; i++)
      if(info[i][0] == '-')
	 if(info[i][1] != 's' && info[i][1] != 'f'){
            cout<<"Invalid commands; -s or -f required."<<endl;
            return false;
         }
   return true;
}

/*
 * Function: getNumStates
 * Description: translates the number of states from a c-line char to an int.
 * Parameters: int, char**, int*
 * Pre-Conditions: the number to be translated can be translated
 * Post-Conditions: numStates holds a positive integer
 */
void getNumStates(int numArgs, char* info[], int* numStates){
   for(int i = 0; i < numArgs; i++)
      if(info[i][0] == '-')
	 if(info[i][1] == 's'){
	    *numStates = atoi(info[i+1]);
	 }
}

/*
 * Function: createStates
 * Description: creates an array of states for the program to read to.
 * Parameters: int
 * Pre-Conditions: numStates is a positive integer
 * Post-Conditions: returns an array of states of size numStates
 */
state* createStates(int numStates){
   state* temp = new state[numStates];
   return temp;
}

/*
 * Function: createCounties
 * Description: creates and array of counties for the program to read to.
 * Parameters: int
 * Pre-Conditions: numCounties is a positive integer
 * Post-Conditions: returns an array of counties of size numCounties
 */
county* createCounties(int numCounties){
   county* temp = new county[numCounties];
   return temp;
}

/*
 * Function: getCountyData
 * Description: reads county data from the .txt file and stores the data in an array.
 * Parameters: int, county*, ifstream&
 * Pre-Conditions: numCounties is a positive integer, c[] is an array of counties, input is an opened .txt file
 * Post-Conditions: each member of c[] is initialized with good data
 */
void getCountyData(int numCounties, county c[], ifstream& input){
   for(int i = 0; i < numCounties; i++){
      input >> c[i].name;
      input >> c[i].population;
      input >> c[i].avgIncome;
      input >> c[i].avgHouse;
      input >> c[i].numCities;
      c[i].cityNames = new string[c[i].numCities];
      for(int j = 0; j < c[i].numCities; j++)
	 input >> c[i].cityNames[j];
   }
}

/*
 * Function: getStateData
 * Description: reads state data from the .txt file and stores the data in an array.
 * Parameters: int, state* ifstream&
 * Pre-Conditions: numStates is a positive integer, s[] is an array of states, input is an opened .txt file
 * Post-Conditions: each member of s[] is initialized with good data
 */
void getStateData(int numStates, state s[], ifstream& input){
   for(int i = 0; i < numStates; i++){
      input >> s[i].name;
      input >> s[i].population;
      input >> s[i].numCounties;
      s[i].c = createCounties(s[i].numCounties);
      getCountyData(s[i].numCounties, s[i].c, input);//fills each county in each state
   }
}

/*
 * Function: deleteInfo
 * Description: frees all memory used in the program
 * Parameters: state*, int
 * Pre-Conditions: none
 * Post-Conditions: all memory is freed
 */
void deleteInfo(state s[], int numStates){
   for(int i = 0; i < numStates; i++){
      for(int j = 0; j < s[i].numCounties; j++)
	 delete [] s[i].c[j].cityNames;//deletes array of cities
      delete [] s[i].c;//deletes array of counties
   }
   delete [] s;//deletes array of states
}
/*
 * Function: largestState
 * Description: prints the name of the state with the largest population.
 * Parameters: state*, int
 * Pre-Conditions: s[] is initialized, numStates is a positive integer
 * Post-Conditions: state with the largest population is printed
 */
void largestState(state s[], int numStates){
   state largest = s[0];
   for(int i = 1; i < numStates; i++)
      if(s[i].population > largest.population)
	 largest = s[i];
   cout<<"Largest state (by population) is: "<<largest.name<<endl;
   cout<<endl;
}

/*
 * Function: largestCounty
 * Description: prints the name of the county with the largest population
 * Parameters: state*, int
 * Pre-Conditions: s[] is initialized, numStates is a positive integer
 * Post-Conditions: county with the largest population is printed
 */
void largestCounty(state s[], int numStates){
   county largest = s[0].c[0];
   for(int i = 0; i < numStates; i++)
      for(int j = 0; j < s[i].numCounties; j++)
	 if(s[i].c[j].population > largest.population)
	    largest = s[i].c[j];
   cout<<"Largest county (by population) is: "<<largest.name<<endl;
   cout<<endl;
}

/*
 * Function: richCounties
 * Description: prints the names of the counties with average incomes above a number
 * Parameters: state*, int, int
 * Pre-Conditions: s[] is initialized, numStates is a positive integer, income is an integer
 * Post-Conditions: names of counties are printed
 */
void richCounties(state s[], int numStates, int income){
   cout<<"Counties with average income above "<<income<<":"<<endl;
   for(int i = 0; i < numStates; i++)
      for(int j = 0; j < s[i].numCounties; j++)
	 if(s[i].c[j].avgIncome > income)
	    cout<<s[i].c[j].name<<", average income: "<<s[i].c[j].avgIncome<<endl;
   cout<<endl;
}

/*
 * Function: averageHouseCost
 * Description: calculates and displays average cost of a house between all states
 * Parameters: state*, int
 * Pre-Conditions: s[] is initialized, numStates is a positive integer
 * Post-Conditions: average house cost is properly calculated and printed
 */
void averageHouseCost(state s[], int numStates){
   int avgCost = 0, count = 0;
   for(int i = 0; i < numStates; i++)
      for(int j = 0; j < s[i].numCounties; j++){
	 avgCost += s[i].c[j].avgHouse;
	 count++;
      }
   avgCost /= count;
   cout<<"Average house cost is: "<<avgCost<<endl;
   cout<<endl;
}

/*
 * Function: sortStateNames
 * Description: sorts states alphabetically by name
 * Parameters: state*, int
 * Pre-Conditions: s[] is initalized and numStates is a positive integer.
 * Post-Conditions: states are sorted alphabetically and the list is printed.
 */
void sortStateNames(state s[], int numStates){
   state hold;
   for(int i = 0; i < numStates; i++)
      for(int j = 0; j < numStates-1-i; j++)
         if(s[j].name > s[j+1].name){
	    hold = s[j];
	    s[j] = s[j+1];
	    s[j+1] = hold;
	 }
   cout<<"States sorted alphabetically by name:"<<endl;
   for(int i = 0; i < numStates; i++)
      cout<<s[i].name<<endl;
   cout<<endl;
}

/*
 * Function: sortCountyNames
 * Description: sorts counties in each state alphabetically by name
 * Parameters: state*, int
 * Pre-Conditions: s[] is initalized and numStates is a positive integer.
 * Post-Conditions: counties are sorted alphabetically and the list is printed.
 */
void sortCountyNames(state s[], int numStates){
   county hold;
   for(int i = 0; i < numStates; i++)
      for(int j = 0; j < s[i].numCounties; j++)
         for(int k = 0; k < s[i].numCounties-1-j; k++)
            if(s[i].c[k].name > s[i].c[k+1].name){
	       hold = s[i].c[k];
	       s[i].c[k] = s[i].c[k+1];
	       s[i].c[k+1] = hold;
	    }
   cout<<"States' counties sorted alphabetically by name:"<<endl;
   for(int i = 0; i < numStates; i++){
      cout<<s[i].name<<":"<<endl;
      for(int j = 0; j < s[i].numCounties; j++)
         cout<<s[i].c[j].name<<endl;
   }
   cout<<endl;
}

/*
 * Function: sortStatePopulation
 * Description: sorts states by increasing population
 * Parameters: state*, int
 * Pre-Conditions: s[] is initalized and numStates is a positive integer.
 * Post-Conditions: states are sorted and the list is printed.
 */
void sortStatePopulation(state s[], int numStates){
   state hold;
   for(int i = 0; i < numStates; i++)
      for(int j = 0; j < numStates-1-i; j++)
         if(s[j].population > s[j+1].population){
	    hold = s[j];
	    s[j] = s[j+1];
	    s[j+1] = hold;
	 }
   cout<<"States sorted by increasing population:"<<endl;
   for(int i = 0; i < numStates; i++)
      cout<<s[i].name<<endl;
   cout<<endl;
}

/*
 * Function: sortCountyPopulation
 * Description: sorts counties by increasing population
 * Parameters: state*, int
 * Pre-Conditions: s[] is initalized and numStates is a positive integer.
 * Post-Conditions: counties are sorted and the list is printed, each state shown.
 */
void sortCountyPopulation(state s[], int numStates){
   county hold;
   for(int i = 0; i < numStates; i++)
      for(int j = 0; j < s[i].numCounties; j++)
         for(int k = 0; k < s[i].numCounties-1-j; k++)
            if(s[i].c[k].population > s[i].c[k+1].population){
	       hold = s[i].c[k];
	       s[i].c[k] = s[i].c[k+1];
	       s[i].c[k+1] = hold;
	    }
   cout<<"States' counties sorted by increasing population:"<<endl;
   for(int i = 0; i < numStates; i++){
      cout<<s[i].name<<":"<<endl;//shows which state's counties are being shown
      for(int j = 0; j < s[i].numCounties; j++)
         cout<<s[i].c[j].name<<endl;
   }
   cout<<endl;
}
