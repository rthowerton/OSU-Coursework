#include <stdio.h>
#include <stdlib.h>

int mutex = 1, full = 0, empty = 3, x = 0;

void consumer(){
   mutex = wait(mutex);
   full = wait(full);
   empty = signal(empty);
   printf("Consumer consumes item %d\n", x);
   x--;
   mutex = signal(mutex);
}

void producer(){
   mutex = wait(mutex);
   full = signal(full);
   empty = wait(empty);
   x++;
   printf("Producer produces item %d\n", x);
   mutex = signal(mutex);
}

int signal(int s){
   return ++s;
}

int wait(int s){
   return --s;
}

int main(){
   int n;
   printf("1. Producer\n2. Consumer\n3. Exit\n");
   while(1){
      printf("Enter your choice: \n");
      scanf("%d", &n);
      switch(n){
	 case 1:
	    if((mutex == 1) && (empty != 0))
	       producer();
	    else
	       printf("Buffer is full!\n");
	    break;
	 case 2:
	    if((mutex == 1) && (full != 0))
	       consumer();
	    else
	       printf("Buffer is empty!\n");
	    break;
	 case 3:
	    exit(0);
	    break;
      }
   }
   return 0;
}
