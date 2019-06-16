#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main(){
   char abc[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','\0'};
   char morse[28][8] = {{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},{".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},{"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."},{"       "},{"   "}};
   
   for(int i = 0; i < 28; i++)
      cout<<abc[i]<<": "<<morse[i]<<endl;
   
   char stuff[16] = "hello world";
   cout<<stuff<<": ";
   for(int i = 0; i < 16; i++){
      if(stuff[i] == ' ')
	 cout<<"       ";
      else
         for(int j = 0; j < 26; j++){
	    if(stuff[i] == abc[j])
	       cout<<morse[j]<<morse[27];
         }
   }
   cout<<endl;

   char code[100] = "....   .   .-..   .-..   ---       .--   ---   .-.   .-..   -..";
   cout<<code<<" : ";
   int pos = 0, q = 1;
   char temp[8];
   for(int i = 0; i < 4; i++){
      if(code[i] != ' ')
         temp[pos] = code[i];
      pos++;
   }
   for(int i = 0; i < 4; i++)
      cout<<temp[i];
   cout<<endl;
   /*for(int i = 0; i < 4; i++){
      if((code[i] != ' ' && code[q] != ' ') || (code[i] == ' ' && code[q] == ' ')){
         temp[pos] = code[i];
	 pos++;
	 q++;
      }
      cout<<temp;
      else if((code[i] != ' ' && code[q] == ' ') || (code[i] == ' ' && code[q] != ' ')){
         temp[pos] = code[i];
	 for(int j = 0; j < 28; j++){
	    if(temp == morse[j])
	       cout<<abc[j];
	 }
	 pos = 0;
	 for(int a = 0; a < 8; a++)
	    temp[a] = '\0';
      }
      q++;
   }*/
   return 0;
}
