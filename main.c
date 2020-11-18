#include "stringOperations.h"
#include "commandExecution.h"
#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    char *input_str, *argsPiped[MAXCOMMANDS];
 		
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\\\\Welcome! Shell for OS UNIX\\\\\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		
	while (1) {
		int validation = 0;
		printf("user: ~unix$ ");
            /* Read from stdin, continue loop if input is empty */
	    if (!readInput(&input_str))
		    continue;
        /* Piped commands */
        int numberOfCommands;
        if ((numberOfCommands = splitByPipe(input_str, argsPiped))) {
            struct command commands[numberOfCommands];
            for (int i=0; i<numberOfCommands; i++) {
                if(splitBySpaces(argsPiped[i], commands[i].args) == 0)
                {
                    printf("Command cannot be executed. Wrong format!\n");
                    validation = 1;			
                    break;
                };
            }
            if(validation != 0)
            {
                validation = 0;
                continue;
            }
            int ret = strcmp(commands[0].args[0], "exit");
            if (ret == 0)
                return 0;
            forkPipes(numberOfCommands, commands);
            }
	    }
    return 0;
}



