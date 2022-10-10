mysh: mysh.o
	gcc -g mysh.o -o mysh

mysh.o: mysh.c mysh.h
	gcc -g -c mysh.c
