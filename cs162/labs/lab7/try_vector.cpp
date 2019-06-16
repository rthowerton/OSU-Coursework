#include "./vector.hpp"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

int main(){
   vector<int> v;
   std::vector<int> stdv;
   
   cout<<v.size()<<endl;
   cout<<stdv.size()<<endl;

   v.push_back(23);
   stdv.push_back(23);

   cout<<v.size()<<endl;
   cout<<stdv.size()<<endl;

   cout<<v[0]<<endl;
   cout<<stdv[0]<<endl;
   
   try{
   	cout<<v.at(2)<<endl;
   }
   catch(std::out_of_range& e){
	cout << e.what() << endl;
   }
   cout<<stdv.at(2)<<endl;

   return 0;
}
