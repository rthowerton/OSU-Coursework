#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
 * Find each wrestler's position in array
 */
int find_pos(char* w, char** wrestlers, int size){
   int pos = 0;
   for(pos; pos < size; pos++){
      if(!strcmp(w, wrestlers[pos])){
         return pos;
      }
   }
}

void print(int* arr, int size){
   for(int i = 0; i < size; i++){
      cout << "[" << arr[i] << "]" << endl;
   }
}

int main(int argc, char** argv){
   /*
    * Check for correct usage
    */
   if(argc != 2){
      cout << "USAGE: a.out wrestler.txt" << endl;
      return -1;
   }
   /*
    * Declare wide-scope variables
    */
   ifstream infile;
   string line;
   int counter, numWrestlers, numRivalries;
   char* tok;
   char** wrestlers, **babyfaces, **heels;
   char*** rivalries;

   // Open the input file
   infile.open(argv[argc-1]);

   // Assure the file is opened before operating
   if(infile.is_open()){
      /*
       * Do my weird method of getting information from the file
       */
      getline(infile, line);
      char* cstr = new char[line.length() + 1];
      strcpy(cstr, line.c_str());
      numWrestlers = atoi(cstr);
      delete[] cstr;
      //cout << numWrestlers << endl;
      /*
       * Get the wrestler's names
       */
      wrestlers = new char*[numWrestlers];
      for(int w = 0; w < numWrestlers; w++){
         getline(infile, line);
         if(!(w == numWrestlers-1))
            line.erase(line.length() - 1);
         wrestlers[w] = new char[line.length() + 1];
         cstr = new char[line.length() + 1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, " ");
         strcpy(wrestlers[w], tok);
         delete[] cstr;
         //cout << wrestlers[w] << endl;
      }

      /*
       * Get the number of rivalries
       */
      getline(infile, line);
      cstr = new char[line.length() + 1];
      strcpy(cstr, line.c_str());
      numRivalries = atoi(cstr);
      delete[] cstr;
      //cout << numRivalries << endl;
      /*
       * Get the rival pairs
       */
      rivalries = new char**[numRivalries];
      for(int r = 0; r < numRivalries; r++){
         rivalries[r] = new char*[2];
         getline(infile, line);
         if(!(r == numRivalries-1))
            line.erase(line.length() - 1);
         cstr = new char[line.length() + 1];
         strcpy(cstr, line.c_str());
         tok = strtok(cstr, " ");
         for(int i = 0; i < 2; i++){
            rivalries[r][i] = new char[strlen(tok) + 1];
            strcpy(rivalries[r][i], tok);
            tok = strtok(NULL, " ");
            //cout << "[" << rivalries[r][i] << "]";
         }
         //cout << endl;
         delete[] cstr;
      }

      /*
       * Do some pairing
       */
      // Temp array
      int* temp = new int[numWrestlers];
      for(int i = 0; i < numWrestlers; i++){
         temp[i] = -1;
      }
      int nb = 0, nh = 0, cur = 0;
      // The first wrestler is a babyface
      temp[0] = 1;
      nb++;
      cur = !cur;
      for(int w = 0; w < numWrestlers; w++){
         // Inverse current wrestler type
         cur = !cur;
         for(int r = 0; r < numRivalries; r++){
            // If the current wrestler is not involved in the rivalry
            if(strcmp(rivalries[r][0], wrestlers[w]) && strcmp(rivalries[r][1], wrestlers[w])){
               continue;
            }
            // If the current wrestler is either side of the rivalry
            else{
               // First
               if(!strcmp(rivalries[r][0], wrestlers[w])){
                  cout << "first" << endl;
                  // Get wrestler's position in set
                  int pos = find_pos(rivalries[r][1], wrestlers, numWrestlers);
                  cout << pos << endl;
                  if(temp[pos] == -1)
                     temp[pos] = cur;
                  else if(temp[pos] == !cur){ // If types don't match
                     cout << "No." << endl;
                     return 2;
                  }
                  break;
               }
               // Second
               else if(!strcmp(rivalries[r][1], wrestlers[w])){
                  cout << "second" << endl;
                  // Get wrestler's position in set
                  int pos = find_pos(rivalries[r][0], wrestlers, numWrestlers);
                  cout << pos << endl;
                  if(temp[pos] == -1)
                     temp[pos] = cur;
                  else if(temp[pos] == !cur){ // If types don't match
                     cout << "No." << endl;
                     return 2;
                  }
                  break;
               }
            }
         }
         if(cur){nb++;}
         else{nh++;}
         print(temp, numWrestlers);
      }
   }
   else{
      cout << "Failed to open " << argv[argc-1] << endl;
      cout << "Exiting" << endl;
      return 1;
   }
   // Free up memory at the end
   for(int w = 0; w < numWrestlers; w++){
      delete[] wrestlers[w];
   }
   delete[] wrestlers;
   for(int a = 0; a < numRivalries; a++){
      for(int b = 0; b < 2; b++){
         delete[] rivalries[a][b];
      }
      delete[] rivalries[a];
   }
   delete[] rivalries;
   return 0;
}