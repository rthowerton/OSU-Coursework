#include <stdio.h>
#include <stdlib.h>

struct item{
   int value;
   int waitTime;
};

struct item buffer[32];

int main(){
   printf("number of items in array (should be 0): %d\n", sizeof(buffer)/sizeof(buffer[0]));
   struct item newItem = {1, 2};
   buffer[0] = newItem;
   printf("new item value = %d\n", buffer[0].value);
   printf("new item waitTime = %d\n", buffer[0].waitTime);
   printf("number of items in array (should be 1): %d\n", sizeof(buffer)/sizeof(buffer[0]));
   return 0;
}
