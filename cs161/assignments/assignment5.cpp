#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main(){
   int pos = 0, size = 2;
   char temp;
   char* input = new char[size];
   while(cin.get(temp) && temp != '\n'){
      input[pos] = temp;
      bool flag = true;
      for(int i = 0; i < size; i++){
	 if(!input[i])
	    flag = false;
      }
      if(flag == true){
	 size += 1;
	 char* input2 = new char[size];
	 for(int i = 0; i < size; i++)
	    input2[i] = input[i];
	 delete[] input;
	 input = input2;
	 delete[] input2;
      }
      pos++;
      cout<<pos<<endl;
      cout<<input<<endl;
   }
   return 0;
}


