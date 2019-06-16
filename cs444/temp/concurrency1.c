#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include "mt19937ar.c"

//item struct, contains two values
struct item{
   int value;
   int waitTime;
};

//buffer to hold produced items
struct item buffer[32];
//the two semaphores from the little book of semaphores, and one type determined by the machine.
int items = 0, spaces = 31, randType = 1;
//the mutex to be used later
pthread_mutex_t theMutex = PTHREAD_MUTEX_INITIALIZER;

int getRandom();
void* produce();
void* consume();
int signal(int);
int wait(int);

int main(int argc, char** argv){
   //determine which rng to use
   unsigned int eax, ebx, ecx, edx;
   char vendor[13];

   eax = 0x01;

   __asm__ __volatile__(
                        "cpuid;"
                        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
			: "a"(eax)
			);

   if(ecx & 40000000){
      //use rdrand
      randType = 1;
   }
   else{
      //use mt19937
      init_genrand(time(NULL));
      randType = 0;
   }

   //some quick user error checking
   int i;
   if(argc != 2){
      printf("Usage: concurrency1 #\nwhere # == number of desired consumer threads.\n");
      exit(-1);
   }
   for(i = 0; i < strlen(argv[1]); i++){
      if(!isdigit(argv[1][i])){
	 printf("InputError: Argument is not a number.\n");
	 exit(1);
      }
   }

   //generating requested number of consumers and producers
   int numCons = atoi(argv[1]);
   pthread_t consumers[numCons], producers[numCons-1];
   for(i = 0; i < numCons; i++)
      pthread_create(&consumers[i], NULL, consume, NULL);
   for(i = 0; i < numCons-1; i++)
      pthread_create(&producers[i], NULL, produce, NULL);

   //destroy consumers and producers, but this is never reached
   for(i = 0; i < numCons; i++)
      pthread_join(consumers[i], NULL);
   for(i = 0; i < numCons-1; i++)
      pthread_join(producers[i], NULL);

   return 0;
}

//get a random value, based on what the machine supports
int getRandom(){
   if(randType){
      int num;
      __asm__ __volatile__(
	                   "rdrand %0;"
			   : "=r"(num)
	    );
      return num;
   }
   else
      return (int)genrand_int32();
}

//consumer function
void* consume(){
   while(1){
      //wait for items to become available
      while(items <= 0)
	 continue;
      //queue up
      items = wait(items);
      //wait for the mutex
      while(pthread_mutex_trylock(&theMutex))
	 continue;
      //get an item from buffer
      struct item toConsume = buffer[items];
      //unlock the mutex
      pthread_mutex_unlock(&theMutex);
      //signal space has been freed up
      spaces = signal(spaces);
      //process item
      sleep(toConsume.waitTime);
      printf("Consumer %d got item %d!\n", pthread_self(), toConsume.value);
   }
}

//producer function
void* produce(){
   while(1){
      //wait before producing
      sleep((getRandom() % 5) + 3);
      //wait for space to add item
      while(spaces <= 0)
	 continue;
      //say that item is being added
      spaces = wait(spaces);
      //wait for the mutex
      while(pthread_mutex_trylock(&theMutex))
	 continue;
      //add item
      struct item toProduce = {items, (getRandom() % 8) + 2};
      buffer[items] = toProduce;
      //unlock the mutex
      pthread_mutex_unlock(&theMutex);
      //signal more items in buffer
      items = signal(items);
   }
}

//increase a value (the little book of semaphores calls it signalling)
int signal(int s){
   return (++s);
}

//decrease a value (the little book of semaphores calls it waiting)
int wait(int w){
   return (--w);
}
