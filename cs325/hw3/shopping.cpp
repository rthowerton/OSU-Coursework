#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

int shoppingSpreeAux(int weight, int** items, int numItems){
   int total = 0;
   // cout << "weight = " << weight << endl;
   // cout << "numItems = " << numItems << endl;
   int arr[weight+1][numItems+1];
   for(int a = 0; a <= weight; a++){
      arr[a][0] = 0;
   }
   for(int b = 0; b <= numItems; b++){
      arr[0][b] = 0;
   }
   for(int i = 1; i <= numItems; i++){
      //cout << "outer loop" << endl;
      for(int w = 0; w <= weight; w++){
         //cout << "inner loop" << endl;
         //cout << "items [" << i-1 << "][" << 1 << "] = " << items[i-1][1] << endl;
         if(items[i-1][1] <= w){
            //cout << "item " << i-1 << " can fit" << endl;
            if((items[i-1][0] + arr[w-items[i-1][1]][i-1]) > arr[w][i-1]){
               //cout << "is more better" << endl;
               arr[w][i] = items[i-1][0] + arr[w-items[i-1][1]][i-1];
            }
            else{
               //cout << "isn't better" << endl;
               arr[w][i] = arr[w][i-1];
            }
         }
         else{
            //cout << "no it can't" << endl;
            arr[w][i] = arr[w][i-1];
         }
      }
   }
   // for(int w = 0; w <= weight; w++){
   //    for(int k = 0; k <= numItems; k++){
   //       if(arr[w][k] > 0){
   //          cout << "w = " << w << endl;
   //          cout << "k = " << k << endl;
   //       }
   //    }
   //    printf("\n");
   // }
   total += arr[weight][numItems];
}

int shoppingSpree(int* fam, int** items, int numFam, int numItems){
   int total = 0;
   for(int f = 0; f < numFam; f++){
      total += shoppingSpreeAux(fam[f], items, numItems);
      // cout << "\n--------------------\n" << endl;
   }
   return total;
}

int main(){
   // Variable declaration
   int total, numTests, numItems, numFam;
   int* fam;
   int** items;
   ofstream outfile;
   ifstream infile;
   string line;

   // Open the files
   outfile.open("shopping.out");
   infile.open("shopping.txt");

   if(infile.is_open()){
      total = 0;
      // Get the number of test cases
      getline(infile, line);
      char* cstr = new char[line.length() + 1]; // Make the line be a C string
      strcpy(cstr, line.c_str());
      char* tok = strtok(cstr, ""); // Tokenize the line to get the number
      numTests = atoi(tok);
      // printf("Number of test cases: %d\n", numTests);
      delete[] cstr;
      // For the number of test cases, get the number of items then the number of family
      for(int a = 0; a < numTests; a++){
         getline(infile, line);
         cstr = new char[line.length() + 1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, "");
         numItems = atoi(tok);
         // printf("Number of items: %d\n", numItems);
         delete[] cstr;
         // Initialize items
         items = new int*[numItems];
         for(int i = 0; i < numItems; i++){
            items[i] = new int[2];
         }
         // For the number of items, get each item's values.
         for(int b = 0; b < numItems; b++){
            getline(infile, line);
            cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            //get item value
            tok = strtok(cstr, " ");
            // printf("btok1 = %s\n", tok);
            items[b][0] = atoi(tok);
            // printf("Value of item %d: %d\n", b, items[b][0]);
            //get item weight
            tok = strtok(NULL, " ");
            // printf("btok2 = %s\n", tok);
            items[b][1] = atoi(tok);
            // printf("Weight of item %d: %d\n", b, items[b][1]);
            delete[] cstr;
         }
         getline(infile, line);
         cstr = new char[line.length() + 1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, "");
         numFam = atoi(tok);
         // printf("Number of family members: %d\n", numFam);
         delete[] cstr;
         //Initialize fam
         fam = new int[numFam];
         // For each family member, get their weight
         for(int c = 0; c < numFam; c++){
            getline(infile, line);
            cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            //get family member's weight class
            tok = strtok(cstr, "");
            // printf("ctok = %s\n", tok);
            fam[c] = atoi(tok);
            // printf("Family member %d's weight: %d\n", c, fam[c]);
            delete[] cstr;
         }
         // Let's go shopping!
         total = shoppingSpree(fam, items, numFam, numItems);
         cout << "Test " << a+1 << " total = " << total << endl;
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
