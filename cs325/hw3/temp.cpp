#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

int main(){
   // Input/Output files
   ofstream outfile;
   ifstream infile;
   // String to hold lines of data.txt
   string line;
   // Generic integer for counting in loops
   int counter;
   // Open the files
   outfile.open("shopping.out");
   infile.open("shopping.txt");
   // Some quick error checking
   if(infile.is_open()){
      // Get the number of test cases
      getline(infile, line);
      // Make the line be a C string
      char* cstr = new char[line.length() + 1];
      strcpy(cstr, line.c_str());
      // Tokenize the line to get the number
      char* tok = strtok(cstr, "");
      // Get the number of number of test cases
      int numTests = atoi(tok);
      printf("Number of test cases: %d\n", numTests);
      delete[] cstr;
      // For the number of test cases, get the number of items
      for(int a = 0; a < numTests; a++){
         getline(infile, line);
         char* cstr = new char[line.length() + 1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, "");
         int numItems = atoi(tok);
         printf("Number of items: %d\n", numItems);
         delete[] cstr;
         // For the number of items, get each item's values.
         for(int b = 0; b < numItems; b++){
            getline(infile, line);
            cout << line << endl;
            cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            //get item value
            tok = strtok(cstr, " ");
            printf("btok1 = %s\n", tok);
            int ip = atoi(tok);
            printf("Value of item %d: %d\n", b, ip);
            //get item weight
            tok = strtok(cstr, " ");
            printf("btok2 = %s\n", tok);
            int iw = atoi(tok);
            printf("Weight of item %d: %d\n", b, iw);
            delete[] cstr;
         }
      // And then the number of family members
         getline(infile, line);
         cstr = new char[line.length() + 1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, "");
         int numFam = atoi(tok);
         printf("Number of family members: %d\n", numFam);
         delete[] cstr;
         // For each family member, get their weight
         for(int c = 0; c < numFam; c++){
            getline(infile, line);
            cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            //get family member's weight class
            tok = strtok(cstr, "");
            printf("ctok = %s\n", tok);
            int fw = atoi(tok);
            printf("Family member %d's weight: %d\n", c, fw);
            delete[] cstr;
         }
      }
   }
   // If the file can't be opened
   else
      cout << "Cannot open data.txt" << endl;
   // Close the files 
   outfile.close();
   infile.close();
   return 0;
}
