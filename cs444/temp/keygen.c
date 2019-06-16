#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEY_SIZE 10
unsigned char crypto_key[KEY_SIZE];

int main(){
   int i;
   unsigned char c;
   srand(time(NULL));
   for(i = 0; i < KEY_SIZE; i++){
      c = rand() % 256;
      crypto_key[i] = c;
      printf("crypto_key[%d] = %d, %c\n", i, crypto_key[i], crypto_key[i]);
   }
   printf("crypto_key = %s\n", crypto_key);
   return 0;
}