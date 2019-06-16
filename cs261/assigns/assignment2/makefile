all: testExercise testDynArray

testExercise: 
	gcc -g -Wall -std=c99 -o exercise dynamicArray.c dynamicArray.h stack_exercise.c stack_exercise.h testExercise.c

testDynArray: 
	gcc -g -Wall -std=c99 -o testda testDynArray.c dynamicArray.c dynamicArray.h 


clean:
	rm exercise
	rm testda
