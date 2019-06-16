#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

struct node{
   struct node* next;
   int val;
};

struct node* head;

int insertMutex = 1, noSearcher = 1, noInserter = 1, searchCounter = 0, insertCounter = 0;

void* delete();
void* insert();
void* search();
int signal(int);
int wait(int);

int main(int argc, char** argv){
   int i;
   //initialize head
   head = malloc(sizeof(struct node));
   head = NULL;

   //initialize random
   srand(time(NULL));

   //pthreads
   int num_searchers = atoi(argv[1]), num_inserters = atoi(argv[2]), num_deleters = atoi(argv[3]);
   pthread_t searchers[num_searchers], inserters[num_inserters], deleters[num_deleters];
   for(i = 0; i < num_searchers; i++)
      pthread_create(&searchers[i], NULL, search, NULL);
   for(i = 0; i < num_inserters; i++)
      pthread_create(&inserters[i], NULL, insert, NULL);
   for(i = 0; i < num_deleters; i++)
      pthread_create(&deleters[i], NULL, delete, NULL);

   for(i = 0; i < num_searchers; i++)
      pthread_join(searchers[i], NULL);
   for(i = 0; i < num_inserters; i++)
      pthread_join(inserters[i], NULL);
   for(i = 0; i < num_deleters; i++)
      pthread_join(deleters[i], NULL);

   return 0;
}

void* delete(){
   while(1){
      //sleep between 2 and 5 seconds
      int to_sleep = (rand() % 4) + 2;
      sleep(to_sleep);
      //printf("in delete\n");
      while(noSearcher != 1)
         continue;
      noSearcher = wait(noSearcher);
      //printf("no searcher\n");
      while(noInserter != 1)
         continue;
      noInserter = wait(noInserter);
      //printf("no inserter\n");
      if(head == NULL)
         printf("No item deleted.\n");
      else if(head->next == NULL){
         printf("Deleted: %d\n", head->val);
         free(head);
         head = NULL;
      }
      else{
         int i;
         struct node* to_delete = head;
         while(to_delete->next->next != NULL)
            to_delete = to_delete->next;
         i = to_delete->next->val;
         free(to_delete->next);
         to_delete->next = NULL;
         printf("Deleted: %d\n", i);
      }
      noInserter = signal(noInserter);
      //printf("now inserter\n");
      noSearcher = signal(noSearcher);
      //printf("now searcher\n");
   }
}

void* insert(){
   //printf("in insert\n");
   while(1){
      if(noInserter == 1)
         noInserter = wait(noInserter);
      //printf("noInserter = %d\n", noInserter);
      insertCounter = signal(insertCounter);
      //printf("insertCounter = %d\n", insertCounter);
      while(insertMutex != 1)
         continue;
      insertMutex = wait(insertMutex);
      int num_to_add = (rand() % 10) + 1;
      struct node* to_add = malloc(sizeof(struct node*));
      to_add->next = NULL;
      to_add->val = num_to_add;
      
      if(head == NULL){
         head = to_add;
         printf("Inserted: %d\n", num_to_add);
      }
      else{
         struct node* elem = head;
         while(elem->next != NULL)
            elem = elem->next;
         elem->next = to_add;
         printf("Inserted: %d\n", num_to_add);
      }
      insertMutex = signal(insertMutex);
      insertCounter = wait(insertCounter);
      //printf("insertCounter = %d\n", insertCounter);
      if(insertCounter == 0)
         noInserter = signal(noInserter);
      //printf("noInserter = %d\n", noInserter);
      //sleep between 2 and 5 seconds
      int to_sleep = (rand() % 4) + 2;
      sleep(to_sleep);
   }
}

void* search(){
   while(1){
      //printf("in search\n");
      if(noSearcher == 1)
         noSearcher = wait(noSearcher);
      searchCounter = signal(searchCounter);
      struct node* elem = head;
      if(elem == NULL)
         return;
      else{
         do{
            printf("Found: %d\n", elem->val);
            elem = elem->next;
         } while(elem != NULL);      
      }
      searchCounter = wait(searchCounter);
      if(searchCounter == 0)
         noSearcher = signal(noSearcher);
      //printf("before search sleep\n");
      //sleep between 2 and 5 seconds
      int to_sleep = (rand() % 4) + 2;
      sleep(to_sleep);
   }
}

int signal(int s){
   return ++s;
}

int wait(int w){
   return --w;
}