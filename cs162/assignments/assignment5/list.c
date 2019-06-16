#include <stdio.h>
#include <stdlib.h>
#include "list.h"
/*
 * Function: length
 * Description: calculates the length of the list
 * Parameters: struct list*
 * Pre-Conditions: list has been initialized and filled
 * Post-Conditions: proper length is returned
 */
int length(struct list* l){
   int count = 0;
   struct node* dummy = l->head->next;
   while(dummy != l->tail){
      count++;
      dummy = dummy->next;
   }
   //printf("length: %d\n", count);
   return count;
}
/*
 * Function: print
 * Description: prints the contents of the list
 * Parameters: struct list
 * Pre-Conditions: list has values and is initialized
 * Post-Conditions: list is printed in order
 */
void print(struct list l){
   printf("Printing.\n");
   int i = 1;
   struct node* dummy = l.head->next;
   while(i <= length(&l)){
      printf("Value %d: %d\n", i, dummy->val);
      dummy = dummy->next;
      i++;
   }
}
/*
 * Function: pushFront
 * Description: adds a number to the front of the list
 * Parameters: struct list*, int
 * Pre-Conditions: list is initialized
 * Post-Conditons: number is added to front of list
 */
void pushFront(struct list* l, int num){
   struct node* dummy = (struct node*) malloc(sizeof(struct node));
   dummy->val = num;
   dummy->next = l->head->next;
   l->head->next->prev = dummy;
   l->head->next = dummy;
   dummy->prev = l->head;
}
/*
 * Function: pushBack
 * Description: adds a number to the back of the list
 * Parameters: struct list*, int
 * Pre-Conditions: list is initialized
 * Post-Conditions: number is added to back of list
 */
void pushBack(struct list* l, int num){
   struct node* dummy = (struct node*) malloc(sizeof(struct node));
   dummy->val = num;
   dummy->prev = l->tail->prev;
   l->tail->prev->next = dummy;
   l->tail->prev = dummy;
   dummy->next = l->tail;
}
/*
 * Function: clear
 * Description: frees all memory associated with the list
 * Parameters: struct list*
 * Pre-Conditions: list exists and user is finished with it
 * Post-Conditions: list has been freed
 */
void clear(struct list* l){
   struct node* dummy = l->head;
   while(dummy != l->tail){
      dummy = dummy->next;
      free(dummy->prev);
   }
   //free(l->tail);
}
/*
 * Function: removeVal
 * Description: removes a value and any copies from the list
 * Parameters: struct list*, int
 * Pre-Conditions: value exists in the initialized list
 * Post-Conditions: value has been removed from list
 */
void removeVal(struct list* l, int num){
   printf("Removing\n");
   struct node* dummy = l->head;
   while(dummy != l->tail){
      dummy = dummy->next;
      if(dummy->val == num){
	 dummy->prev->next = dummy->next;
	 dummy->next->prev = dummy->prev;
	 free(dummy);
	 dummy = l->head;
      }
   }
}
/*
 * Function: sortAscending
 * Description: sorts the list values in ascending order
 * Parameters: struct list*
 * Pre-Conditions: list has been initialized with values
 * Post-Conditions: list has been sorted in ascending order
 */
void sortAscending(struct list* l){
   printf("Sorting in ascending order.\n");
   struct list* temp;
   temp->head = (struct node*) malloc(sizeof(struct node));
   temp->tail = (struct node*) malloc(sizeof(struct node));
   temp->head->next = temp->tail;
   temp->tail->prev = temp->head;
   int max = length(l), i, num;
   while(length(temp) < max){
      struct node* dummy = l->head->next;
      num = dummy->val;
      for(i = 0; i < length(l); i++){
	 if(num > dummy->next->val){
	    num = dummy->next->val;
	    dummy = dummy->next;
	 } 
	 else{
	    dummy = dummy->next;
	 }
      }
      removeVal(l, num);
      pushBack(temp, num);
      pushBack(temp, num);
   }
   clear(l);
   l->head = temp->head;
   l->tail = temp->tail;
}
/*
 * Function: sortDescending
 * Description: sorts list in descending order
 * Parameters: struct list*
 * Pre-Conditions: list has been initialized with values
 * Post-Conditions: list has been sorted in descending order
 */
void sortDescending(struct list* l){
   printf("Sorting in descending order.\n");
   struct list* temp;
   temp->head = (struct node*) malloc(sizeof(struct node));
   temp->tail = (struct node*) malloc(sizeof(struct node));
   temp->head->next = temp->tail;
   temp->tail->prev = temp->head;
   int max = length(l), i, num;
   while(length(temp) < max){
      struct node* dummy = l->head->next;
      num = dummy->val;
      for(i = 0; i < length(l); i++){
	 if(num > dummy->next->val){
	    num = dummy->next->val;
	    dummy = dummy->next;
	 } 
	 else{
	    dummy = dummy->next;
	 }
      }
      removeVal(l, num);
      pushFront(temp, num);
      pushFront(temp, num);
   }
   clear(l);
   l->head = temp->head;
   l->tail = temp->tail;
}
/*
 * Function: insert
 * Description: inserts a value into a specified position
 * Parameters: struct list*, int, int
 * Pre-Conditions: list has been initialized
 * Post-Conditions: value exists at position in list
 */
void insert(struct list* l, int pos, int num){
   struct node* dummy = (struct node*) malloc(sizeof(struct node));
   dummy->val = num;
   struct node* index = l->head;
   int i = 0;
   while(i < pos-1){
      index = index->next;
      i++;
   }
   index->next->prev = dummy;
   dummy->next = index->next;
   dummy->prev = index;
   index->next = dummy;
}
