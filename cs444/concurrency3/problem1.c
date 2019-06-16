#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

//semaphores to track the number of processes and the availability of the resource
int num_processes = 0;

//function pre-definitions
void* process();
int signal(int);
int wait(int);

int main(int argc, char** argv){
   //seed random
   srand(time(NULL));
	//some quick user error checking
   int i;
	if(argc != 2){
		printf("Usage: problem1 #\nwhere # == number of desired threads.\n");
		exit(-1);
	}
	for(i = 0; i < strlen(argv[1]); i++){
		if(!isdigit(argv[1][i])){
		printf("InputError: Argument is not a number.\n");
		exit(1);
      }
   }

	//pthread initialize and destroy
   int num_threads = atoi(argv[1]);
	pthread_t sharing_threads[num_threads];
	for(i = 0; i < num_threads; i++)
		pthread_create(&sharing_threads[i], NULL, process, NULL);

	for(i = 0; i < num_threads; i++)
		pthread_join(sharing_threads[i], NULL);

	return 0;
}

void* process(){
   while(1){
      //if the number of processes == 3, wait until the number of processes == 0
      //before moving on.
      if(num_processes == 3){
         while(num_processes != 0)
            continue;
      }
      //claim the resource
      num_processes = signal(num_processes);
      //use the resource for random time between 1 and 10 seconds
      int use_resource = rand() % 10 + 1;
      printf("I am process %d and I am using the resource for %d seconds.\n", pthread_self(), use_resource);
      sleep(use_resource);
      //release the resource
      num_processes = wait(num_processes);
   }
} 

int signal(int s){
   return(++s);
}

int wait(int w){
   return(--w);
}