#include <iostream>
#include <fstream>
using namespace std;
#include "letters.h"

int main(){
   ifstream input; string filename;
   cout<<"Give me a file!!!"<<endl;
   cin>>filename;
   input.open(filename);
   int nums[26];
   count_letters(input, &nums);
   return 0;
}
