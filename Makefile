lab1_IO:
	gcc lab1_IO.c -o lab1_IO -lpthread -lm
compile:
	gcc -Wall -g -c lab1_IO.c -o lab1_IO.o
matrix:
	gcc matrixgen.c -o matrixgen
clean:
	rm lab1_IO
	rm lab1_IO.O
compress:
	tar -cvf ECE420Lab1.tar lab1_IO.c names.txt Makefile Readme lab1_IO.h matrixgen.c timer.h serialtester.c instructions.txt