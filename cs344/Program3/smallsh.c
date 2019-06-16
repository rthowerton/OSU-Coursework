#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

//global variable to check if foreground-only mode is active
int tstp = 0;

//change tstp value
void catchSIGTSTP(int signo){
   if(tstp == 0){
      tstp = 1;
      char* message ="\nentering foreground-only mode (& is now ignored)\n";
      write(1, message, 50);
   }
   else{
      tstp = 0;
      char* message = "\nexiting foreground-only mode\n";
      write(1, message, 30);
   }
}

int main(){
   //handle SIGINT and SIGTSTP
   struct sigaction SIGTSTP_action = {0}, ignore_action = {0}, default_action = {0};

   SIGTSTP_action.sa_handler = catchSIGTSTP;
   sigfillset(&SIGTSTP_action.sa_mask);
   SIGTSTP_action.sa_flags = 0;

   ignore_action.sa_handler = SIG_IGN;
   default_action.sa_handler = SIG_DFL;
   sigaction(SIGTSTP, &SIGTSTP_action, NULL);
   sigaction(SIGINT, &ignore_action, NULL);

   //store future child process IDs
   size_t bg_size = 128;
   pid_t* bg_children = (pid_t*)malloc(sizeof(pid_t) * bg_size);
   
   //exit/termination number, for-loop counter
   int xt_status = 0, i;
   
   //initialize bg_children pids to be -5
   for(i = 0; i < bg_size; i++)
      bg_children[i] = -5;

   while(1){
      //check for background process completion
      for(i = 0; i < bg_size; i++){
      int bgChildExitMethod = -5;//background process exit method

	 if(bg_children[i] != -5){//if process is active
	    waitpid(bg_children[i], &bgChildExitMethod, WNOHANG);
	    if(bgChildExitMethod != -5){
	       if(WIFEXITED(bgChildExitMethod)){//if process exited
	          xt_status = WEXITSTATUS(bgChildExitMethod);
	          printf("background pid %d is done: exit value %d\n", bg_children[i], xt_status);
		  bg_children[i] = -5;
	       }
	       else if(WIFSIGNALED(bgChildExitMethod)){//if process was terminated
	          xt_status = WTERMSIG(bgChildExitMethod);
	          printf("background pid %d is done: terminated by signal %d\n", bg_children[i], xt_status);
		  bg_children[i] = -5;
	       }
	    }
	 }
      } 

      //input and argument array initialization
      size_t input_size = 2048, arg_size = 512, arg_length = 16;
      char* input = (char*)malloc(sizeof(char) * input_size);
      char** args = (char**)malloc(sizeof(char) * arg_size);
      //input/output file names
      char* input_file = (char*)malloc(sizeof(char) * arg_length);
      char* output_file = (char*)malloc(sizeof(char) * arg_length);
      //set each argument to NULL string
      for(i = 0; i < arg_size; i++)
	 args[i] = NULL;
      
      //current loop process id stuff
      pid_t spawn_pid = -5;
      int childExitMethod = -5;
      
      //prompt user for input
      write(1, ": ", 2);
      fflush(stdout);
      getline(&input, &input_size, stdin);

      //expand $$
      char* temp;
      char* c;
      
      while((c = strstr(input, "$$")) != NULL){
	 *c = 0;
	 c += 2;
	 temp = malloc(snprintf(NULL, 0, "%s%d%s", input, getpid(), c) + 1);
	 sprintf(temp, "%s%d%s", input, getpid(), c);
	 input = temp;
      }

      //break input into tokens
      int arg_count = 0;
      char* tokens;
      
      tokens = strtok(input, " \n");
      if(tokens == NULL)
	 continue;
      else
	 args[arg_count] = tokens;
      arg_count++;
      while(tokens != NULL){
         tokens = strtok(NULL, " \n");
	 if(tokens == NULL)
	    break;
	 else
	    args[arg_count] = tokens;
         arg_count++;
      }
      
      //if comment, continue
      if(args[0][0] == '#')
	 continue;
      //if exit
      else if(strcmp(args[0], "exit") == 0)
	 exit(0);
      //if cd
      else if(strcmp(args[0], "cd") == 0){
	 if(arg_count == 1){
            chdir(getenv("HOME"));
	    char cwd[40];
	    getcwd(cwd, sizeof(cwd));
	    printf("%s\n", cwd);
	 }
	 else{
	    chdir(args[1]);
	    char cwd[40];
	    getcwd(cwd, sizeof(cwd));
	    printf("%s\n", cwd);
	 }
      }
      //if status
      else if(strcmp(args[0], "status") == 0)
	 printf("%d\n", xt_status);
      else{
	 //if last argument is &, and foreground-only mode not enabled, start in background
	 if((strcmp(args[arg_count-1], "&") == 0) && (tstp == 0)){
	    int in = 0, out = 0;//check if in/out redirection is provided
	    args[arg_count-1] = NULL;//don't pass & to exec
	    spawn_pid = fork();
	    switch(spawn_pid){
	       case -1://if fork failed
		  perror("Background fork failed.\n");
		  exit(1);
		  break;
	       case 0://child
		  sigaction(SIGTSTP, &ignore_action, NULL);
		  for(i = 0; i < arg_size; i++){
		     if(args[i] == NULL)//if there are no arguments
			break;
		     else if(strcmp(args[i], "<") == 0){//redirect stdin
			in = 1;
			args[i] = NULL;
			i++;
			strcpy(input_file, args[i]);
			if(access(input_file, F_OK) == -1){
			   printf("cannot open %s for input\n", input_file);
			   exit(1);
			}
			args[i] = NULL;
		     }
		     else if(strcmp(args[i], ">") == 0){//redirect stdout
			out = 1;
			args[i] = NULL;
			i++;
			strcpy(output_file, args[i]);
			args[i] = NULL;
		     }
		  }
		  if(in == 1){//if input redirection is provided
		     int input_desc = open(input_file, O_RDONLY);
		     dup2(input_desc, 0);
		  }
		  else{//redirect from /dev/null
		     int input_desc = open("/dev/null", O_RDONLY);
		     dup2(input_desc, 0);
		  }
		  if(out == 1){//if output redirection is provided
		     int output_desc = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		     dup2(output_desc, 1);
		  }
		  else{//redirect from /dev/null
		     int output_desc = open("/dev/null", O_WRONLY, 0644);
		     dup2(output_desc, 1);
		  }
		  execvp(args[0], args);
		  perror("Background exec failed.\n");
		  exit(1);
		  break;
	       default://parent
		  for(i = 0; i < bg_size; i++){
		     if(bg_children[i] == -5){
			bg_children[i] = spawn_pid;
			printf("background pid is %d\n", bg_children[i]);//print background process id
			break;
		     }
		  }
		  break;
	    }
	 }
	 //if last argument is & and tstp == 1, go to next prompt
	 else if(tstp == 1)
	    continue;
	 //otherwise start in foreground
	 else{
            spawn_pid = fork();
            switch(spawn_pid){
               case -1://fork failed
	          perror("Foreground fork failed.\n");
	          exit(1);
	          break;
               case 0://child
		  sigaction(SIGINT, &default_action, NULL);
		  sigaction(SIGTSTP, &ignore_action, NULL);
		  for(i = 0; i < arg_size; i++){
		     if(args[i] == NULL)//if no arguments given
			break;
		     else if(strcmp(args[i], "<") == 0){//redirect stdin
			args[i] = NULL;
			i++;
			strcpy(input_file, args[i]);
			if(access(input_file, F_OK) == -1){
			   printf("cannot open %s for input\n", input_file);
			   exit(1);
			}
			args[i] = NULL;
		     }
		     else if(strcmp(args[i], ">") == 0){//redirect stdout
			args[i] = NULL;
			i++;
			strcpy(output_file, args[i]);
			args[i] = NULL;
		     }
		  }
		  int input_desc = open(input_file, O_RDONLY);
		  int output_desc = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		  dup2(input_desc, 0);
		  dup2(output_desc, 1);
	          execvp(args[0], args);
	          perror("exec failed\n");
		  xt_status = 1;
	          exit(xt_status);
	          break;
               default://parent
	          waitpid(spawn_pid, &childExitMethod, 0);//wait on child to finish executing
	          if(WIFEXITED(childExitMethod)){//if child exited normally
		     xt_status = WEXITSTATUS(childExitMethod);
		  }
		  else if(WIFSIGNALED(childExitMethod)){//if child was terminated
		     xt_status = WTERMSIG(childExitMethod);
		     printf("\nterminated by signal %d\n", xt_status);
		  }
	          break;
            }
	 }
      }
   }
}
