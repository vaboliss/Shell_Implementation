#include "stringOperations.h"
#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
/* Reads input from stdin, returns 0 if there are no commands */
int readInput(char** input_str) 
{  
    	size_t  input_len = 0;
    	int len;
    	size_t  n;
	
	len = getline(input_str, &input_len, stdin);
       /* Find length excluding the newline at end */
	if (len > 0)
       		 n = strcspn(*input_str, "\r\n");
    	else
        	 n = 0;
   	 if (n > (size_t)0) {
        	/* Terminate input command before the newline */
        	(*input_str)[n] = '\0';
        	return 1;
    	} else {
        	return 0;
   	 }
}

/* Splits string by pipe symbols */
int splitByPipe(char* str, char** str_piped) 
{ 
	int i; 
	for (i = 0; i < MAXCOMMANDS; i++) { 
		str_piped[i] = strsep(&str, "|"); 
		if (str_piped[i] == NULL) 
			break; 
	} 
	return i;  
} 

/* Splits string by spaces */
int splitBySpaces(char* str, char** string_list) 
{  
	int i;
	for (i = 0; i < MAXCOMMANDS; i++) { 
		string_list[i] = strsep(&str, " "); 

		if (string_list[i] == NULL) 
			break; 

		if (strlen(string_list[i]) == 0) 
			i--; 
	} 
	return i;
} 
