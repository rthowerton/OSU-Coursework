#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(){
   /*
    * Declare variables
    */
   ifstream infile;
   string line;
   int counter, numActs, num, start, end;
   int** arr;

   // Open the file
   infile.open("act.txt");

   if(infile.is_open()){
      while(getline(infile, line)){
         counter++;
         char* cstr = new char[line.length() + 1]; // Make the line be a C string
         strcpy(cstr, line.c_str());
         char* tok = strtok(cstr, " ."); // Tokenize the line to get the number of activities
         numActs = atoi(tok);
         cout << "Set " << counter << endl; // Print the set number
         /*
          * Declare arr to hold the set
          */
         arr = new int*[numActs];
         for(int a = 0; a < numActs; a++){
            arr[a] = new int[3];
         }
         delete[] cstr;
         /*
          * Fill out arr for current activity set
          */
         for(int i = 0; i < numActs; i++){
            getline(infile, line);
            char* cstr = new char[line.length() + 1]; // Make the line be a C string
            strcpy(cstr, line.c_str());
            tok = strtok(cstr, " ."); // Tokenize the line to get the number of activities
            arr[i][0] = atoi(tok);
            for(int j = 1; j < 3; j++){
               tok = strtok(NULL, " .");
               arr[i][j] = atoi(tok);
            }
            delete[] cstr;
         }
         /*
          * Sort arr in ascending order of start times
          */
         for(int a = 1; a < numActs; a++){
            int* temp = arr[a];
            int b = a-1;
            while(b >= 0 && arr[b][1] > temp[1]){
               arr[b+1] = arr[b];
               b = b-1;
            }
            arr[b+1] = temp;
         }
         /*
          * Choose the latest possible start times from the top down
          * Store the values in a temp array, initialized to be the
          * same size as the input array.
          */
         int* temp = new int[numActs];
         int* cur = new int[3];
         cur = arr[numActs-1];
         temp[0] = cur[0]; // Because the last activity always starts last
         int pos = 1; // Because the first slot is taken
         for(int a = numActs-2; a >= 0; a--){
            if(arr[a][2] > cur[1])
               continue;
            else{
               cur = arr[a];
               temp[pos] = cur[0];
               pos++;
            }
         }
         /*
          * Print out the list in reverse order
          */
         printf("Number of activities selected = %d\n", pos);
         printf("Activities: ");
         for(int a = pos-1; a >= 0; a--){
            printf("%d ", temp[a]);
         }
         printf("\n");
         delete[] temp;
         /*
          * Clear out arr for later use
          */
         for(int a = 0; a < numActs; a++){
            delete[] arr[a];
         }
         delete[] arr;
      }
   }
   // If the file can't be opened
   else
      cout << "Cannot open act.txt" << endl;
   // Close the file 
   infile.close();
   return 0;
}