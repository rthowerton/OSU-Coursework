#include <iostream>
#include <cstdlib>
using namespace std;

int** createArray(int rows);
void towers(int disks, int** b, int from_col, int to_col, int spare);
#define COLS 3

int main(int argc, char* argv[]){
   int disks = atoi(argv[1]);
   int from_col = 1, to_col = 2, spare = 3, num = 1;
   int** b = createArray(disks);
   for(int i = 0; i < disks; i++){
     for(int j = 0; j < COLS; j++){
	if(j == from_col-1){
	   b[i][j] = num;
	}
	else
	   b[i][j] = 0;
     }
     num++;
   }
   cout<<"---------\n";
   for(int i = 0; i < disks; i++){
      for(int j = 0; j < COLS; j++)
	 cout<<"["<<b[i][j]<<"]";
      cout<<endl;
   }
}

int** createArray(int rows){
   int** b;
   b = new int*[rows];
   for(int i = 0; i < rows; i++)
      b[i] = new int[3];
   return b;
}
void towers(int disks, int **b, int from_col, int to_col, int spare){
   if(disks >= 1){
      towers(disks-1, b, from_col, spare, to_col);
      for(int row = 0; row < disks; row++){
         if(b[row][from_col] != 0){
	    for(int destRow = 1; destRow >= 0; destRow--){
	       if(b[destRow][to_col] == 0){
	          b[row][from_col] = b[destRow][to_col];
		  b[row][from_col] = 0;
		  break;
	       }
	    }
	    break;
	 }
      }
   }
   for(int i = 0; i < disks; i++){
      for(int j = 0; j < COLS; j++)
	 cout<<"["<<b[i][j]<<"]";
      cout<<endl;
   }
   towers(disks-1, b, spare, to_col, from_col);
}
