CC=g++
exe=mult_div
$(exe): mult_div.o prog.o
	$(CC) mult_div.o prog.o -o $(exe)
mult_div.o: mult_div.cpp
	$(CC) -c mult_div.cpp
prog.0: prog.cpp
	$(CC) -c prog.cpp
clean:
	rm -f *.out *.o $(exe)
