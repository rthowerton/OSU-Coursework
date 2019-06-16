#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int length(char array[]);

int main(){
   char abc[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','\0'};
   char morse[28][9] = {{".-   \0"},{"-...   \0"},{"-.-.   \0"},{"-..   \0"},{".   \0"},{"..-.   \0"},{"--.   \0"},{"....   \0"},{"..   \0"},{".---   \0"},{"-.-   \0"},{".-..   \0"},{"--   \0"},{"-.   \0"},{"---   \0"},{".--.   \0"},{"--.-   \0"},{".-.   \0"},{"...   \0"},{"-   \0"},{"..-   \0"},{"...-   \0"},{".--   \0"},{"-..-   \0"},{"-.--   \0"},{"--..   \0"},{"       \0"}};
   
   char code[21] = "-...   ---   -...   ";
   cout<<code<<" : ";
   int count = 0;
   for(int i = 0; i < length(code);){
      for(int j = 0; j < 27; j++){
	 for(int k = 0; k < length(morse[j]); k++){
	    if(code[i+k] == morse[j][k]){
	       count++;
	    }
	    else{
	       count = 0;
	       break;
	    }
	    if(count == length(morse[j])){
	       cout<<abc[j];
	       count = 0;
	       j = 27;
	       i += k+1;
	    }
	 }
      }
   }
   cout<<endl;
   return 0;
}

int length(char array[]){
   char x = array[0];
   int num = 0;
   for(num; x != '\0'; num++){
      x = array[num];
   }
   return num-1;
}
