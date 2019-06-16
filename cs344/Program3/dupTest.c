#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void main(){
   int file_desc = open("tricky.txt", O_CREAT| O_WRONLY | O_APPEND);

   dup2(file_desc, 1);
   printf("I will be printed in the file tricky.txt\n");
}
