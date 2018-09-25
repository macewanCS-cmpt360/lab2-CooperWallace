#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

/*
 * CMPT360 Lab 2
 * Cooper Wallace
 *
 * A Simple Shell
 */

int main(void)
{
	char *cmdline;
	char *token = NULL;
	int i, rc;
	char *args[10];

	// Flag for waiting until execution is complete.
	int wait_exec;


	while (true) {
		cmdline = calloc(1, 1024);
		wait_exec = false;
		i = 0;

		printf("prompt> ");
		fgets(cmdline, 1024, stdin);

		token = strtok(cmdline, "\n ");
		while (token != NULL) {
			//printf("%s\n", token);
			args[i++] = strdup(token);
			token = strtok(NULL, "\n ");
		}
		args[i] = NULL;

		// Check if command is to be put in background
		if (strlen(args[i-1]) == 1 && args[i-1][0] == '&') {
			args[i-1] = NULL;
			wait_exec = true;
		}

		free(cmdline);

		/* Extending functionality */
		rc = fork();

		if (rc < 0) {
			fprintf(stderr, "Failed forking\n");
			exit(1);
		} else if (rc == 0)
			// Execute command in Child process
			execvp(args[0], args);
		else {
			if (!wait_exec)
				wait(NULL);
		}
	}

	return 0;
}


