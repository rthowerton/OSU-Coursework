#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void merge(int* arr, int l, int m, int r){
   int i, j, k;
   int n1 = m - l + 1;
   int n2 = r - m;
   // Temp arrays
   int L[n1], R[n2];
   // Copy data to temp arrays
   for(i = 0; i < n1; i++){
      L[i] = arr[l + i];
   }
   for(j = 0; j < n2; j++){
       R[j] = arr[m + 1 + j];
   }
   // Merge the temp arrays back into arr
   i = 0;
   j = 0;
   k = l;
   while(i < n1 && j < n2){
      if(L[i] <= R[j]){
         arr[k] = L[i];
         i++;
      }
      else{
         arr[k] = R[j];
         j++;
      }
      k++;
   }
   // Copy the remaining elements of L if there are any
   while(i < n1){
      arr[k] = L[i];
      i++;
      k++;
   }
   // Copy the remaining elements of R if there are any
   while(j < n2){
      arr[k] = R[j];
      j++;
      k++;
   }
}

void mergeSort(int* arr, int l, int r){
   if(l < r){
      int m = l + (r-l)/2;
      // Do some sort
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);

      merge(arr, l, m, r);
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
   /*
   * The idea for the timer was borrowed from
   * https://stackoverflow.com/questions/3220477/how-to-use-clock-in-c
   */
   // Clock counter
   clock_t start;
   double duration;
   // Open the files
   outfile.open("merge.out");
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
         cout << "Array size: " << i << endl;
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
         // Start the clock
         start = clock();
         /*
         * The following algorithm was borrowed from 
         * https://www.geeksforgeeks.org/merge-sort/
         */
         mergeSort(arr, 0, i-1);
         // Calculate the time
         duration = (clock() - start)/(double)CLOCKS_PER_SEC;
         cout << "Merge Sort time: " << duration << endl;
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