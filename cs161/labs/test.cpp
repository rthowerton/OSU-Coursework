#include <iostream>

using namespace std;

int main()
{
   int answer;
   cout<<"Do you like the vi editor? 1 = yes, 0 = no: "<<endl;
   cin>>answer;
   if(answer == 1)
      cout<<"You love vi!"<<endl;
   else
      cout<<"You hate vi!"<<endl;
   return 0;
}
