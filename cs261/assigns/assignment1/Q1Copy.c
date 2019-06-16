/* CS261 - Assignment 1 - Q. 1*/
/* Name: Ryan Howerton
 * Date: 9/30/2016
 * Solution description: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
   int id;
   int score;
};

struct student* allocate(){
   /*Allocate memory for ten students*/
   struct student* temp = (struct student*) malloc(sizeof(struct student)*10);
   /*return the pointer*/
   return temp;
}

void generate(struct student* students){
   for(int i = 0; i < 10; i++){
      students[i].id = i;
      students[i].score = (10*i)%50;
   }
}

void output(struct student* students){
   /* Output information about the ten students in the format:
    * ID1 score1
    * ID2 score2
    * etc...*/
   for(int i = 0; i < 10; i++){
      printf("ID: %d score: %d\n", students[i].id, students[i].score);
   }
}

int min(struct student* students){
   /* return the minimum score*/
   int min = students[0].score;
   for(int i = 0; i < 10; i++){
      if(students[i].score < min)
	 min = students[i].score;
   }
   return min;
}

float avg(struct student* students){
   /* return the average score*/
   int sum = 0, count = 0, avg;
   for(int i = 0; i < 10; i++){
      sum += students[i].score;
      count++;
   }
   avg = sum/count;
   return avg;
}

void sort(struct student* students){
   /* sort the students by score from min to max*/
   struct student temp;
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
         if(students[j+1].score < students[j].score){
	    temp.id = students[j].id; temp.score = students[j].score;
            students[j].id = students[j+1].id; students[j].score = students[j+1].score;
	    students[j+1].id = temp.id; students[j+1].score = temp.score;
         }
      }
   }
}

void deallocate(struct student* students){
   /* deallocate memory from stud */
   /*if(students == NULL)
      return;
   else
      for(int i = 0; i < 10; i++)
	 free(students[i]);*/
   free(students);
}

int main(){
   struct student* stud = NULL;
   stud = allocate();
   generate(stud);
   output(stud);
   sort(stud);
   output(stud);
   for(int i = 0; i < 10; i++){
      printf("%d %d\n", stud[i].id, stud[i].score);
   }
   printf("Avg: %f\n", avg(stud));
   printf("Min: %d\n", min(stud));
   return 0;
}
