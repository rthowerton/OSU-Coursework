#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dynamicArray.h"


int in_stack(DynArr * s,char tofind){
   /* 
      Returns 1 if the element `tofind` is present in DynArr `s`, 0
      otherwise.  Upon returning `s` should have its elements in the
      same order as when the function is called. In other words, you
      may modify `s` but must return it to its original state

      You may only call the following funcitons

         DynArr *createDynArr(int cap);
         int isEmptyDynArr(DynArr *v);
         void pushDynArr(DynArr *v, TYPE val);
         TYPE topDynArr(DynArr *v);
         void popDynArr(DynArr *v);

      Hint: use another stack to hold elements while you search
      and then restore the initial state of `s`
   */
   //create a temp DynArr to hold values
   DynArr* temp = createDynArr(s->capacity);
   char hold, i, j;
   //iterate through *s searching for the value tofind
   for(i = s->size-1; i >= 0 || hold == tofind; i--){
      hold = topDynArr(s);//hold gets the top value of s
      if(hold != tofind){//if hold is not tofind
	 pushDynArr(temp, hold);//put hold on top of temp
	 popDynArr(s);//pop off of s
      }
      else if(hold == tofind && !isEmptyDynArr(temp)){//if hold == to tofind and temp is not empty
         for(j = temp->size-1; j >= 0; j--){//iterate through temp
	    pushDynArr(s, topDynArr(temp));//return values to s
	    popDynArr(temp);
	 }
	 return 1;//found tofind
      }
      else{//if hold == tofind and temp is empty
	 return 1;//found tofind
      }
   }
   for(j = temp->size-1; j >= 0; j--){//iterate through temp
      pushDynArr(s, topDynArr(temp));//return values to s
      popDynArr(temp);
   }
   return 0;//did not find tofind
}





int valid_bracket(char * str){
   /*
     str contains only bracking characters - parenthesis ( '(' and ')'
     ), square brackets ('[' and ']') and squiggly brackets ('{' and
     '}')

     This function returns 1 if str contains a set of balanced
     bracketing characters and zero otherwise.  A string is said to
     have balanced bracketing characters if each opening bracket ( '(',
     '{' and '[') contains a correspodning closing bracket
     (')','}',']') of the same type and brackets are closed in the
     reverse order that they are opened.

     For example 

     valid_bracket("{}[]()") returns 1
     valid_bracket("{][}(]") returns 0, the brackets do not match
     valid_bracket("(([]))") returns 1
     valid_bracket("(([)])") returns 0, 
          because the '(' at index 1 is closed by the ')' at index 3
	  before the '[' at index 2 is closed

     valid_bracket("}") returns 0 because there is no opening bracket for '{'

     valid_bracket("({}[])") returns 1
     valid_bracket("({}([]))") returns 1
     valid_bracket("({}([]){([])})") returns 1
     valid_bracket("({([]))") returns 0

   */
   int length = strlen(str), i, j;
   if(length % 2 != 0)
      return 0;
   if(str[0] == ')' || str[0] == ']' || str[0] == '}')
      return 0;
   
   char* copy = (char*) malloc(sizeof(char)*length);
   for(i = 0; i < length; i++)
      copy[i] = str[i];
   
   char hold;
   for(i = 0; i < length; i++){
      hold = copy[i];
      for(j = length-1; j > i; j--){
	 if(hold == '('){
	    if(copy[j] == ')'){
	       if((j - i) % 2 != 0){
		  copy[i] = '-';
		  copy[j] = '-';
		  break;
	       }
	       else
		  return 0;
	    }
	 }
	 else if(hold == '['){
	    if(copy[j] == ']'){
	       if((j - i) % 2 != 0){
		  copy[i] = '-';
		  copy[j] = '-';
		  break;
	       }
	       else
		  return 0;
	    }
	 }
	 else if(hold == '{'){
	    if(copy[j] == '}'){
	       if((j - i) % 2 != 0){
		  copy[i] = '-';
		  copy[j] = '-';
		  break;
	       }
	       else
		  return 0;
	    }
	 }
      }
   }
   for(i = 0; i < length; i++){
      hold = copy[i];
      if(hold != '-')
	 return 0;
   }
   return 1;
}


