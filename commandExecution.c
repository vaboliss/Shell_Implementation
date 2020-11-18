#include "commandExecution.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <fcntl.h>

int pipe(int pipefd[2]);
int pipe2(int pipefd[2], int flags);

/* Starts process to execute command. 'in' - cmd input, 'out' - cmd output */
void startProcess(int in, int out, struct command *cmd)
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        if (in != 0)
        {
            dup2(in, 0);
            close(in);
        }
        if (out != 1)
        {
            dup2(out, 1);
            close(out);
        }

        if (execvp(cmd->args[0], cmd->args) < 0)
        {
            printf("\nCould not execute command\n");
        }
        exit(0);
    }
    else
    {
	return;    
	}
}

/* Creates and connects pipes */
void forkPipes(int n, struct command *cmd)
{
    int i;
    pid_t pid, wpid;
    int in = 0;
    int out = 1;
    int status = 0;

    /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
    for (i = 0; i < n - 1; ++i)
    {
        int fd[2];
        pipe2(fd, O_CLOEXEC);
        out = fd[1];
        //f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
        startProcess(in, out, cmd + i);
        /* No need for the write end of the pipe, the child will write here.  */
        if (in != STDIN_FILENO)
        {
            close(in);
        }
        if (out != STDOUT_FILENO)
        {
            close(out);
        }
        close(out);
        /* Keep the read end of the pipe, the next child will read from there.  */
        in = fd[0];
    }
    /* Execute the last stage command. */
    pid = fork();

    if (pid == 0)
    {

        if (in != 0)
        {
            dup2(in, 0);
            close(in);
        }
        if (execvp(cmd[i].args[0], cmd[i].args) < 0)
        {
            printf("\nCould not execute command\n");
        }
        exit(0);
    }
    if (in != STDIN_FILENO)
    {
        close(in);
    }

    if (out != STDOUT_FILENO)
    {
        close(out);
    }

    while ((wpid = wait(&status)) > 0);
}
