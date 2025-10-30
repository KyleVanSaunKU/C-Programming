CC = g++
CFLAGS = -Wall -g


Lab_9_Matrix_Operations: C++_Programming_Main.o
	$(CC) $(CFLAGS) -o Lab_9_Matrix_Operations C++_Programming_Main.o


C++_Programming_Main.o: C++_Programming_Main.cpp
	$(CC) $(CFLAGS) -c C++_Programming_Main.cpp


clean:
	rm -f *.o Lab_9_Matrix_Operations
