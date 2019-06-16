#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(){
   pid_t spawn_pid = -5;
   int childExitStatus = -5;
   
   spawn_pid = fork();
   switch(spawn_pid){
      case -1:
	 perror("Fork failed.\n");
	 exit(1);
	 break;
      case 0:
	 printf("CHILD(%d): Sleeping for 1 second\n", getpid());
	 sleep(1);
	 printf("CHILD(%d): Converting into \'ls -a\'\n", getpid());
	 execlp("ls", "ls", "-a", NULL);
	 perror("CHILD: exec failure!\n");
	 exit(2);
	 break;
      default:
	 printf("PARENT(%d): Sleeping for 2 seconds\n", getpid());
	 sleep(2);
	 printf("PARENT(%d): Wait()ing for child(%d) to terminate\n", getpid(), spawn_pid);
	 pid_t actual_pid = waitpid(spawn_pid, &childExitStatus, 0);
	 printf("PARENT(%d): Child(%d) terminated, exiting!\n", getpid(), actual_pid);
	 exit(0);
	 break;
   }
}
