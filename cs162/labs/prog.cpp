#include <iostream>
using namespace std;
#include "./mult_div.h"
int main(int argc, char** argv){
   int rows, cols, cont = 1;
   while(cont == 1){
      bool okay = checkDimensions(argv[1], argv[2]);
      if(okay == 1){
         integerize(&rows, &cols, argv[1], argv[2]);
         squares** table = makeTable(rows, cols);
         setMult(table, rows, cols);
         setDiv(table, rows, cols);
      }
      cout<<"Continue? 1 = yes, 0 = no: "<<endl;
      cin>>cont;
      if(cont == 0)
	 break;
      else{
	 cout<<"Rows:"<<endl;
	 cin>>argv[1];
	 cout<<"Cols:"<<endl;
	 cin>>argv[2];
      }
   }
   return 0;
}
