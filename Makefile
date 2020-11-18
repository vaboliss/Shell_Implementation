makeAntra: main.o commandExecution.o stringOperations.o  	
		gcc -Wall main.o commandExecution.o stringOperations.o -o antra.o

main.o: main.c main.h commandExecution.h stringOperations.h
	gcc -c -Wall main.c

commandExecution.o: commandExecution.c commandExecution.h	
	gcc -c -Wall commandExecution.c
	

stringOperations.o: stringOperations.c stringOperations.h
	gcc -c -Wall stringOperations.c	


clean: 
	rm -f *.o
