#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
using std::ofstream;
using std::string;
using std::stringstream;

int main(){
   srand(time(NULL));
   ofstream outfile("hundredthousandreverse.txt");
   char c; int i = 99999;
   while(i >= 0){
      //int gen = rand() % 1000000;
      stringstream s;
      s << i;
      string num = s.str();
      num.push_back(' ');
      for(int pos = 0; pos < num.length(); pos++){
         c = num[pos];
         outfile.put(c);
      }
      i--;
   }
   return 0;
}
