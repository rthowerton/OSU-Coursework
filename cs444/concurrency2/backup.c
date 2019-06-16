#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

struct philosopher{
	char* name;
	int left, right, neighbor_l, neighbor_r, index;
};

struct philosopher philos[5];

int forks[5] = {1, 1, 1, 1, 1};

pthread_mutex_t the_mutex = PTHREAD_MUTEX_INITIALIZER;

void eat(struct philosopher*);
void get_forks(struct philosopher*);
void init_philo(struct philosopher*, int);
void* philosophize(void*);
void put_forks(struct philosopher*);
int signal(int);
void think(struct philosopher*);
int wait(int);

int main(){
	int i;
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

void eat(struct philosopher* p){
	pthread_mutex_unlock(&the_mutex);
	int to_eat = (rand() % 8) + 2;
	printf("I, %s, will now eat for %d seconds.\n", p->name, to_eat);
	sleep(to_eat);
}

void get_forks(struct philosopher* p){
	printf("I, %s, am now hungry and need forks %d and %d.\n", p->name, p->left, p->right);
	pthread_mutex_lock(&the_mutex);
	while(forks[p->left] == 0 || forks[p->right] == 0){
		continue;
	}
	forks[p->left] = wait(forks[p->left]);
	forks[p->right]= wait(forks[p->right]);
	printf("I, %s, have acquired my forks %d and %d.\n", p->name, p->left, p->right);
}

void init_philo(struct philosopher* p, int i){
	//seed random
	srand(time(NULL));
	//name the philosophers
	switch(i){
		case 0:
			p->name = (char*) malloc(5 * sizeof(char));
			strcpy(p->name, "Kant");
			break;
		case 1:
			p->name = (char*) malloc(10 * sizeof(char));
			strcpy(p->name, "Aristotle");
			break;
		case 2:
			p->name = (char*) malloc(10 * sizeof(char));
			strcpy(p->name, "Descartes");
			break;
		case 3:
			p->name = (char*) malloc(9 * sizeof(char));
			strcpy(p->name, "Epicurus");
			break;
		case 4:
			p->name = (char*) malloc(7 * sizeof(char));
			strcpy(p->name, "Hobbes");
			break;
	}
	//determine ints
	p->left = i;
	p->right = (i + 1) % 5;
	p->neighbor_l = (i + 4) % 5;
	p->neighbor_r = (i + 1) % 5;
	p->index = i;
}

void* philosophize(void* philo){
	struct philosopher* p = (struct philosopher*)philo;
	//printf("Hello world! My name is %s and my neighbors are %s and %s!\n", p->name, philos[p->neighbor_l].name, philos[p->neighbor_r].name);
	while(1){
		//printf("forks: %d | %d | %d | %d | %d\n", forks[0], forks[1], forks[2], forks[3], forks[4]);
		think(p);
		get_forks(p);
		eat(p);
		put_forks(p);
	}
}

void put_forks(struct philosopher* p){
	printf("I, %s, have finished eating.\n", p->name);
	forks[p->left] = signal(forks[p->left]);
	forks[p->right]= signal(forks[p->right]);
	printf("I, %s, have released my forks %d and %d.\n", p->name, p->left, p->right);
}

int signal(int s){
	return ++s;
}

void think(struct philosopher* p){
	int to_think = (rand() % 20) + 1;
	printf("I, %s, will now think for %d seconds.\n", p->name, to_think);
	sleep(to_think);
}

int wait(int w){
	return --w;
}