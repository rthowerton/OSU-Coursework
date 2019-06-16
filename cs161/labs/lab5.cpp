#include <iostream>
#include <string>

using namespace std;

void get_sentence(string&);

int main(){
   string words;
   get_sentence(words);
   return 0;
}

void get_sentence(string &s){
   cout<<"Enter your stream of consciousness: ";
   getline(cin, s);
   cout<<"Your things: "<<s<<endl;
}
