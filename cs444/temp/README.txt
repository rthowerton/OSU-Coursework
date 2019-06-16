   This first concurrency assignment is an implementation of a solution
to the Producer-Consumer Problem. The .tar.bz2 file downloaded includes
a concurrency1.c file that implements the solution, a mt19937ar.c file 
that provides a random number generator to those processors that do not
support Intel's RDRAND hardware random number generator, and a Makefile
that can compile and clean the solution. To compile and run this       
solution enter the following commands ($ indicates prompt):            
   $ make
   $ concurrency1 [number of desired consumer threads]
This will cause the concurrency1 solution to run forever or until a    
kill command is sent to the process via Ctrl-C or Ctrl-Z. If the user  
wishes to remove the .exe, then the user can run:                      
   $ make clean
which will delete the concurrency1.exe.                                
