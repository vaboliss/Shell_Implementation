#include "main.h"

struct command {
	char *args[MAXCOMMANDS];
};

void startProcess (int in, int out, struct command *cmd);
void forkPipes (int n, struct command *cmd);


