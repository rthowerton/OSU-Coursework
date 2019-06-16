#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>


struct Link* listInsertionSort(struct Link* head) {

  /*
   * This function should perform an insertion sort on the list whose head is
   * provided as the function's argument, so that the values in the list are
   * sorted in ascending order, starting at the head.
   *
   * The sort should be done without allocating any new Link structs or any
   * other auxiliary data structures.
   *
   * Return a pointer to the new head of the list.
   */
   if(head == NULL)
      return head;
   struct Link *hold, *next, *prev, *pos = head;
   while(pos->next != NULL){
      prev = pos;
      pos = pos->next;
      struct Link *current = head;
      while(current != pos){
	 if(current->value < pos->value)
	    current = current->next;
	 else if(current->value >= pos->value){
	    next = pos->next;
	    hold = current->next;
	    current->next = pos;
	    current->next->next = hold;
	    prev->next = next;
	    pos = prev;
	    break;
	 }
	 /*else if(current->value >= pos->value){
	    next = pos->next;
	    pos->next = current;
	    prev->next = next;
	    pos = prev;
	    break;
	 }*/
      }
   }

   return head;

}


struct Link* reverseList(struct Link* head) {

  /*
   * This function should iteratively reverse the list whose head is provided
   * as the function's argument.
   *
   * The reversal must be done totally in place, i.e. you may not allocate any
   * new Link structs or any other auxiliary data structures.
   *
   * Return a pointer to the new head of the list.
   */
   if(head == NULL)
      return head;
   
   struct Link *pos = head, *temp;
   //search for end of list
   while(pos->next != 0)
      pos = pos->next;
   temp = pos;//assign temp to last link of list
   
   //iterate through list adding values directly after temp
   struct Link *cur = head;
   while(cur != temp){
      struct Link *hold = temp->next;//track rest of list
      temp->next = cur;//set temp->next = current link
      pos = cur->next;//track cur->next
      temp->next->next = hold;//tack on rest of list after temp->next
      cur = pos;//cur goes to cur->next
   }
   
   //head gets reset to temp
   head = temp;
   
   return head;
}


struct Link* reverseListRecursive(struct Link* head){

  /*
   * Write this function for extra credit.  It should do the exact same thing
   * as reverseList() above, except it should do it recursively instead of
   * iteratively (i.e. no loops allowed).
   *
   * Again, you may not allocate any new Link structs or any other auxiliary
   * data structures.  You may, however, define an auxiliary function to help
   * you do the recursion.
   *
   * Return a pointer to the new head of the list.
   */
  return head;

}
