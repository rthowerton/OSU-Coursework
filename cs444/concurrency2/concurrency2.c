#include "concurrency2.h"

int main(){
	//variable for use in for loops
	int i;
	//seed random
	srand(time(NULL));
	//initialize the philosophers
	for(i = 0; i < 5; i++){
		init_philo(&philos[i], i);
	}
	//initialize the threads
	pthread_t philothreads[5];
	for(i = 0; i < 5; i++){
		//printf("making thread %s\n", philos[i]);
		pthread_create(&philothreads[i], NULL, &philosophize, (void*)&philos[i]);
	}
	//join the threads
	for(i = 0; i < 5; i++){
		pthread_join(philothreads[i], NULL);
	}
	return 0;
}