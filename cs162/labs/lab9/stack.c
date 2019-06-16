#include <stdio.h>
#include <stdlib.h>
struct node{
   int val;
   struct node* next;
};

struct stack{
   struct node* head;
   struct node* tail;
};

void init(struct stack* s){
   s->head = NULL;
   s->tail = NULL;
}

void push(struct stack* s, int temp){
   struct node* newNode = (struct node*) malloc(sizeof(struct node));
   newNode->val = temp;
   newNode->next = s->head;
   if(s->head == NULL){
      s->head = newNode;
      s->tail = newNode;
   }
   else
      s->head = newNode;
}

/*int pop(struct stack* s){

}*/

int main(){
   struct stack* s;
   init(s);
   //push(s, 12);
   return 0;
}
