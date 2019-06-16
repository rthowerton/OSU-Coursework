#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#include "./mult_div.h"

bool checkDimensions(char* r, char* c){
   bool okay = true;
   if((*r <= 49 || *r >= 57) || (*c <= 49 || *c > 57))
      okay = false;
   return okay;
}

void integerize(int* rows, int* cols, char* arg1, char* arg2){
   *rows = atoi(arg1);
   *cols = atoi(arg2);
}

squares** makeTable(int rows, int cols){
   squares** table = new squares*[rows];
   for(int i = 0; i < cols; i++)
      table[i] = new squares[cols];
   return table;
}

void setMult(squares** table, int rows, int cols){
   for(int i = 1; i <= rows; i++)
      for(int j = 1; j <= cols; j++)
	 table[i-1][j-1].mult = i*j;
   cout<<"Multiplication Table:"<<endl;
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++)
	 cout<<"["<<table[i][j].mult<<"]";
      cout<<endl;
   }
}

void setDiv(squares** table, int rows, int cols){
   for(int i = 1; i <= rows; i++)
      for(int j = 1; j <= cols; j++)
	 table[i-1][j-1].div = (float)i/(float)j;
   cout<<"Division Table:"<<endl;
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++)
	 cout<<"["<<table[i][j].div<<"]";
      cout<<endl;
   }
}

void deleteTable(squares** table, int row){
   for(int i = 0; i < row; i++)
      delete [] table[row];
}
