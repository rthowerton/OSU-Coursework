#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct Bin{
   int space;
   int numItems;
};

int main(){
   ifstream infile;
   string line;
   int numCases, binSize, numItems, numBins = 0;
   int* items;
   Bin* arr, *temp;
   // Open the input file
   infile.open("bin.txt");
   if(infile.is_open()){
      // Get the number of test cases in the file
      getline(infile, line);
      char* cstr = new char[line.length()+1];
      strcpy(cstr, line.c_str());
      char* tok = strtok(cstr, "");
      numCases = atoi(tok);
      delete[] cstr;
      //cout << "Number of test cases: " << numCases << endl;
      for(int a = 0; a < numCases; a++){
         // Get the bin size for this case
         getline(infile, line);
         cstr = new char[line.length()+1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, "");
         binSize = atoi(tok);
         delete[] cstr;
         //cout << "Size of bin " << a << " = " << binSize << endl;
         // Get the number of items for this case
         getline(infile, line);
         cstr = new char[line.length()+1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, "");
         numItems = atoi(tok);
         delete[] cstr;
         //cout << "Number of items in case " << a << " = " << numItems << endl;
         // Instantiate an array of Bins
         arr = new Bin[1];
         arr[0].space = binSize;
         arr[0].numItems = 0;
         numBins++;
         // Get the list of items for this case
         items = new int[numItems];
         getline(infile, line);
         cstr = new char[line.length()+1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, " ");
         items[0] = atoi(tok);
         //cout << "items[0] = " << items[0] << endl;
         for(int b = 1; b < numItems; b++){
            tok = strtok(NULL, " ");
            items[b] = atoi(tok);
            //cout << "items[" << b << "] = " << items[b] << endl;
         }
         delete[] cstr;
         /*
          * First do first-fit
          */
         for(int c = 0; c < numItems; c++){
            int i = 0;
            while(i < numBins){
               if(arr[i].space - items[c] >= 0){ // if the item can fit, fit it
                  arr[i].space -= items[c];
                  arr[i].numItems++;
                  break;
               }
               else // go to the next bin
                  i++;
            }
            if(i == numBins){ // if the item failed to fit in any bin, make a new bin
               numBins++;
               temp = new Bin[numBins];
               for(int d = 0; d < numBins-1; d++){
                  temp[d] = arr[d];
               }
               //delete[] arr;
               arr = temp;
               arr[numBins-1].space = binSize - items[c];
               arr[numBins-1].numItems = 1;
            }
         }
         cout << "Test Case " << a+1 << " First Fit: " << numBins << " - ";
         numBins = 0;
         /*
          * Then do first-fit decreasing
          */
         // Sort in descending order and do the same thing as above
         for(int e = 1; e < numItems; e++){
            int hold = items[e];
            int f = e-1;
            while(f >= 0 && items[f] < hold){
               items[f+1] = items[f];
               f--;
            }
            items[f+1] = hold;
         }
         for(int g = 0; g < numItems; g++){
            int i = 0;
            while(i < numBins){
               if(arr[i].space - items[g] >= 0){ // if the item can fit, fit it
                  arr[i].space -= items[g];
                  arr[i].numItems++;
                  break;
               }
               else // go to the next bin
                  i++;
            }
            if(i == numBins){ // if the item failed to fit in any bin, make a new bin
               numBins++;
               temp = new Bin[numBins];
               for(int h = 0; h < numBins-1; h++){
                  temp[h] = arr[h];
               }
               //delete[] arr;
               arr = temp;
               arr[numBins-1].space = binSize - items[g];
               arr[numBins-1].numItems = 1;
            }
         }
         cout << " First Fit Decreasing: " << numBins << endl;
         numBins = 0;
      }
   }
   else{
      cout << "Failed to open bin.txt, exiting" << endl;
      infile.close();
      return -1;
   }
   infile.close();
   return 0;
}