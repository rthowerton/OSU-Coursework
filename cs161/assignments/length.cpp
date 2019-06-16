#include <iostream>
using namespace std;
int length(char array[]);

int main(){
   char morse[28][9] = {{".-\0"},{"-...\0"},{"-.-.\0"},{"-..\0"},{".\0"},{"..-.\0"},{"--.\0"},{"....\0"},{"..\0"},{".---\0"},{"-.-\0"},{".-..\0"},{"--\0"},{"-.\0"},{"---\0"},{".--.\0"},{"--.-\0"},{".-.\0"},{"...\0"},{"-\0"},{"..-\0"},{"...-\0"},{".--\0"},{"-..-\0"},{"-.--\0"},{"--..\0"},{"       \0"},{"   \0"}};
   cout<<length(morse[6])<<endl;
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
