#include <iostream>
#include <string.h>

using namespace std;

int main(){
   cout << strcmp("A\0", "A") << endl;
   return 0;
}
