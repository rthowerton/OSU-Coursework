#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

//Philosopher struct
struct philosopher{
	char* name;
	int left, right, neighbor_l, neighbor_r, index;
};

struct philosopher philos[5];//List of philosopher structs

int forks[5] = {1, 1, 1, 1, 1};//List of forks available to the philosophers

pthread_mutex_t the_mutex = PTHREAD_MUTEX_INITIALIZER;//The mutex

void eat(struct philosopher*);
void get_forks(struct philosopher*);
void init_philo(struct philosopher*, int);
void* philosophize(void*);
void put_forks(struct philosopher*);
int signal(int);
void think(struct philosopher*);
int wait(int);

//The philosopher unlocks the mutex before 'eating' for a random amount of time between
//2 and 9 seconds.
void eat(struct philosopher* p){
	pthread_mutex_unlock(&the_mutex);
	int to_eat = (rand() % 8) + 2;
	printf("I, %s, will now eat for %d seconds.\n", p->name, to_eat);
	sleep(to_eat);
}

//The philosopher announces that he is hungry, then waits on the mutex.
//After locking the mutex, the philosopher waits on its forks to become available.
//The philosopher claims the forks then announces it.
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

//Initialize the philosophers to have a name, know its left and right forks,
//know its left and right neighbors, and know its index in the list.
void init_philo(struct philosopher* p, int i){
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
	//determine struct ints
	p->left = i;
	p->right = (i + 1) % 5;
	p->neighbor_l = (i + 4) % 5;
	p->neighbor_r = (i + 1) % 5;
	p->index = i;
}

//This is the working function. Philosophers think, then vie for forks,
//then eat, then put their forks back.
void* philosophize(void* philo){
	struct philosopher* p = (struct philosopher*)philo;
	while(1){
		think(p);
		get_forks(p);
		eat(p);
		put_forks(p);
	}
}

//Philosophers announce that they are done eating, then place their forks
//and announce as such.
void put_forks(struct philosopher* p){
	printf("I, %s, have finished eating.\n", p->name);
	forks[p->left] = signal(forks[p->left]);
	forks[p->right]= signal(forks[p->right]);
	printf("I, %s, have released my forks %d and %d.\n", p->name, p->left, p->right);
}

//Signal that the fork is available for use.
int signal(int s){
	return ++s;
}

//Philosophers think for a random amount of time and announce the length.
void think(struct philosopher* p){
	int to_think = (rand() % 20) + 1;
	printf("I, %s, will now think for %d seconds.\n", p->name, to_think);
	sleep(to_think);
}

//Signal that the fork is claimed.
int wait(int w){
	return --w;
}