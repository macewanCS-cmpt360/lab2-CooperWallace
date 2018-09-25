#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * CMPT360 Lab 2
 * Cooper Wallace
 *
 * Question 7
 * Write a program that creates a child process, and then in the child closes
 * standard output (STDOUT FILENO). What happens if the child calls printf()
 * to print some output after closing the descriptor?
 */

int main(int argc, char *argv[])
{
	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "Failed forking\n");
		exit(1);
	} else if (rc == 0) {
		close(STDOUT_FILENO);
		printf("This won't be seen\n");
	} else
		printf("This text can be seen\n");

	/* If the child calls printf() after closing the descriptor for
	 * stdout, then cannot output anything to the shell. This can
	 * be replaced with a new descriptor by opening a new file, but
	 * since only close the descriptor we cannot output anything.
	 */
	return 0;
}
