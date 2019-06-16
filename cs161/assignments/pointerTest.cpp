#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

string getString(){
   string s;
   cout<<"Enter a string: ";
   cin>> s;
   return s;
}

void getString(string &str){
   cout<<"Enter a string for ref: ";
   cin>>str;
}

void getString(string *str){
   cout<<"Enter a string for pointer: ";
   cin>> *str;
}

int main(){
   string s;

   s = getString();
   cout<<s<<endl;

   getString(s);
   cout<<s<<endl;

   getString(&s);
   cout<<s<<endl;

   return 0;
}
