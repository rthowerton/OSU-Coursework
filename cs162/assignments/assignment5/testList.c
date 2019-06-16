/*
 * Program: testList.c
 * Author: Ryan Howerton
 * Date: 6/9/2016
 * Description: Creates, sorts, and edits a doubly linked list.
 * Input: None
 * Output: None
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
   char filename[20];
   struct list l;
   l.head = (struct node*) malloc(sizeof(struct node));
   l.tail = (struct node*) malloc(sizeof(struct node));
   l.head->next = l.tail;
   l.tail->prev = l.head;
   FILE* fileptr;
   char num[3], rem[3], pos[3], ins[3];

   printf("Enter filename: ");
   scanf("%s", filename);//get the filename
   fileptr = fopen(filename,"r");//open the file
   while(fscanf(fileptr, "%s", num) != EOF){//scan numbers from the file
      printf("number is: %d\n", atoi(num));
      pushFront(&l, atoi(num));
      pushBack(&l, atoi(num));
   }
   printf("Length of list: %d\n", length(&l));//print length of list
   print(l);
   sortAscending(&l);//sort in ascending order
   print(l);
   sortDescending(&l);//sort in descending order
   print(l);
   printf("Enter a value to remove from list: ");
   scanf("%s", rem);
   printf("Removing the value %d from list.\n", atoi(rem));
   removeVal(&l, atoi(rem));//remove specified number from list
   print(l);
   printf("Enter a number to insert into the list: ");
   scanf("%s", ins);
   printf("Enter a location to insert into: ");
   scanf("%s", pos);
   insert(&l, atoi(pos), atoi(ins));//insert number into position of list
   print(l);
   clear(&l);
   return 0;
}
