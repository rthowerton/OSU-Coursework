#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(){
   char* input = malloc(11);
   sprintf(input, "test$$");
   char* temp;
   char* i;

   while((i = strstr(input, "$$")) != NULL){
      printf("%c\n", *i);
      *i = 0;
      printf("before i shenanigans\n");
      i += 2;
      printf("after i shenanigans\n");
      printf("%s\n", i);
      //int pid = getpid();
      //printf("%d\n", pid);
      temp = malloc(snprintf(NULL, 0, "%s%d%s", input, getpid(), i) + 1);
      printf("after malloc\n");
      sprintf(temp, "%s%d%s", input, getpid(), i);
      free(input);
      input = temp;
      printf("%s\n", input);
   }
}
