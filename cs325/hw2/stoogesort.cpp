#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void stoogeSort(int* arr, int l, int r){
   if((r-l+1) == 2 && (arr[l] > arr[r])){
      printf("l = %d, r = %d\n", l, r);
      int temp = arr[l];
      arr[l] = arr[r];
      arr[r] = temp;
   }
   else if ((r-l+1) > 2){
         double m = ceil(2*((double) (r-l+1))/3.0f);
         stoogeSort(arr, 0, m-1);
         stoogeSort(arr, r-m+1, r);
         stoogeSort(arr, 0, m-1);
   }
}

int main(){
   // Input/Output files
   ofstream outfile;
   ifstream infile;
   // String to hold lines of data.txt
   string line;
   // Generic integer for counting in loops
   int counter;
   // Open the files
   outfile.open("stooge.out");
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
         // Get the number of numbers on the line
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
         // Sort the array
         stoogeSort(arr, 0, i-1);
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