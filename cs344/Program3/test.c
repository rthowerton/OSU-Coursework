#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(){
   pid_t spawnPid = -5;
   int childExitMethod = -5, i;

   spawnPid = fork();
   switch(spawnPid){
      case -1:
	 perror("Hull Breach!\n");
	 exit(1);
      case 0:
	 for(i = 1; i <= 100000; i++)
	    printf("i = %d\n", i);
	 exit(0);
   }

   printf("PARENT: PID: %d, waiting...\n", spawnPid);
   waitpid(spawnPid, &childExitMethod, 0);
   if(WIFEXITED(childExitMethod)){
      int exitStatus = WEXITSTATUS(childExitMethod);
      printf("PARENT: Child process terminated with exit status %d, exiting!\n", exitStatus);
   }
   else if(WIFSIGNALED(childExitMethod)){
      int termSig = WTERMSIG(childExitMethod);
      printf("PARENT: Child process terminated with signal number %d, exiting!\n", termSig);
   }
   exit(0);
}
