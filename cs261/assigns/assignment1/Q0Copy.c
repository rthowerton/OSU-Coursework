/* CS261 - Assignment 1 - Q. 0*/
/* Name: Ryan Howerton
 * Date: 9/30/2016
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

int fooB(int* a, int* b, int c){
   c = *a + *b;
   *a = *b;
   *b = (*b)*2;
   return c;
}

void fooA(int* iptr){
   printf("iptr value: %d\n", *iptr);//print value pointed to by iptr
   printf("Address pointed to: %p\n", iptr);//print the address pointed to
   printf("iptr address: %p\n", &iptr);//print the address of iptr itself
}

int main(){
   /*declare an integer x*/
   int x = 5;
   /*print the address of x*/
   printf("address of x: %p\n", &x);
   /*call fooA() with the address of x*/
   fooA(&x);
   /*print the value of x*/
   printf("value of x: %d\n", x);
   return 0;
}
