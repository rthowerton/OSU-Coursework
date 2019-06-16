#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

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
   outfile.open("insert.out");
   infile.open("data.txt");
   // Some quick error checking
   if(infile.is_open()){
      // For every line of data.txt
      while(getline(infile, line)){
         // Make the line be a C string
         char* cstr = new char[line.length() + 1];
         strcpy(cstr, line.c_str());
         // Tokenize the line to get all the numbers into the array
         char* tok = strtok(cstr, " ");
         // Get the number of numbers on the lin
         int i = atoi(tok);
         // If there's only one, or no numbers on the line, then it's already sorted
         if(i <= 1)
            continue;
         // Integer array to hold line numbers
         int* arr = new int[i];
         // Move to start of list
         tok = strtok(NULL, " ");
         counter = 0;
         while(tok != 0){
            // cout << tok << endl;
            arr[counter] = atoi(tok);
            counter++;
            tok = strtok(NULL, " ");
         }
         /*
         * The following algorithm was borrowed from 
         * https://www.geeksforgeeks.org/insertion-sort/
         * because the way I wanted to do it originally
         * had too many for-loops involved to be efficient.
         */
         int a, b, key;
         for(a = 1; a < i; a++){
            key = arr[a];
            b = a-1;
            while(b >= 0 && arr[b] > key){
               arr[b+1] = arr[b];
               b = b-1;
            }
            arr[b+1] = key;
         }
         // Print sorted array into outfile
         for(counter = 0; counter < i; counter++){
            outfile << arr[counter] << " ";
         }
         outfile << '\n';
         // Free the C string
         delete[] cstr;
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