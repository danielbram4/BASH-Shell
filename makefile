mysh: mysh.o stringOps.o signalHandlers.o shellOps.o commandLineOps.o
	gcc -g mysh.o stringOps.o signalHandlers.o shellOps.o commandLineOps.o -o mysh

mysh.o: mysh.c mysh.h
	gcc -g -c mysh.c

stringOps.o: stringOps.c stringOps.h
	gcc -g -c stringOps.c

signalHandlers.o: signalHandlers.c signalHandlers.h 
	gcc -g -c signalHandlers.c

shellOps.o: shellOps.c shellOps.h 
	gcc -g -c shellOps.c

commandLineOps.o: commandLineOps.c commandLineOps.h 
	gcc -g -c commandLineOps.c



