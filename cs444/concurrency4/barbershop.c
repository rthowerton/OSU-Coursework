#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

int seats, barber = 1, num_customers = 0, barber_chair = 1;

void* barber();
void* customer();
void cut_hair(int);
void get_hair_cut(int);
void live_life();
int signal(int);
int wait(int);

int main(int argc, char** argv){
   int i;
   srand(time(NULL));
   //check to make sure that the argument is a number
   if(argc != 2){
      printf("USAGE: barbershop X\nWhere X is a positive number.\n");
      return 1;
   }
   for(i = 0; i < strlen(argv[1]); i++){
      if(!isdigit(argv[1][i])){
         printf("USAGE: barbershop X\nWhere X is a positive number.\n");
         return 1;
      }
   }
   //set the number of seats
   seats = atoi(argv[1]);
   
   return 0;
}

void* barber(){
   while(1){
      if(num_customers == 0)
         continue;
      else{
         printf("Next customer!\n");
         cut_hair(5);
      }
   }
}

void* customer(){
   while(1){
      if(num_customers == seats){
         live_life();
      }
      else if(!barber_chair){
         seats = signal(seats);
         //wait for hair cut, these elses should probably be a mutex try lock
      }
      else{
         get_hair_cut(5);
      }
   }
}

void cut_hair(int time){
   sleep(time);
}

void get_hair_cut(int time){
   sleep(time);
}

void live_life(){
   int living_life = (rand() % 50) + 1;
   printf("I will wait %d seconds until my next hair cut.\n");
   sleep(living_life);
}

int signal(int s){
   return ++s;
}

int wait(int w){
   return --w;
}