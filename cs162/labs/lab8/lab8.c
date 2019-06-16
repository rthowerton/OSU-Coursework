#include <stdio.h>
#include <stdlib.h>

struct stack{
   int* contents;
   int top;
};

void init(struct stack* s){
   s->contents = (int*) malloc(sizeof(int)*0);
   s->top = 0;
}

void push(struct stack* s, int num){
   int* temp = (int*) malloc(sizeof(int)*(s->top) + 1);
   int i, j;
   for(i = 0; i < s->top; i++)
      temp[i] = s->contents[i];
   free(s->contents);
   s->contents = (int*) malloc(sizeof(int)*((s->top) + 1));
   for(j = 0; j < s->top + 1; j++)
      s->contents[j] = temp[j];
   free(temp);
   s->contents[s->top + 1] = num;
   s->top++;
}

int pop(struct stack* s){
   int store = s->contents[s->top], i, j;
   int* temp = (int*) malloc(sizeof(int)*((s->top) - 1));
   for(i = 0; i < (s->top - 1); i++)
      temp[i] = s->contents[i];
   free(s->contents);
   s->contents = (int*) malloc(sizeof(int)*(s->top) - 1);
   for(j = 0; j < s->top - 1; j++)
      s->contents[j] = temp[j];
   free(temp);
   s->top--;
   return store;
}

int peek(struct stack s){
   return s.contents[s.top];
}

void destroy(struct stack* s){
   free(s->contents);
}

int empty(struct stack s){
   if(s.top == 0)
      return 1;
   else
      return 0;
}

int size(struct stack s){
   return s.top;
}

//main!!!!!!!!!!!!!!
int main(){
   struct stack myStack;
   init(&myStack);
   push(&myStack, 20);
   push(&myStack, 30);
   printf("Is empty: %d \n", empty(myStack));
   printf("Stack size: %d \n", size(myStack));
   printf("Top value: %d \n", peek(myStack));
   printf("Popped: %d \n", pop(&myStack));
   printf("Is empty: %d \n", empty(myStack));
   printf("Stack size: %d \n", size(myStack));
   destroy(&myStack);
}
