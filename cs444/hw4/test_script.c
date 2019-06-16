#include <stdio.h>
#include <sys/syscall.h>

int main(void){
   long frag = syscall(SYS_getpid);
   printf("percent fragmentation: %ld\n", frag);
   return 0;
}