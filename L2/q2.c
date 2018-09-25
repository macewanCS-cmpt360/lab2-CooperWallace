#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * CMPT360 Lab 2
 * Cooper Wallace
 *
 * Question 2
 * Write a program that opens a file (with the open() system call) and then
 * calls fork() to create a new process. Can both the child and parent access
 * the file descriptor returned by open()? What happens when they are
 * writing to the file concurrently, i.e., at the same time?
 */

int main(int argc, char *argv[])
{
	/*
	 * The file descriptor opened before the fork can be accessed
	 * by both the Parent and Child process. Both the Child and
	 * the Parent will write to the file 50 times.
	 */
	int fd = open("test.out", O_CREAT | O_WRONLY, 0700);
	char process_name[128];
	int rc = fork();

	if (rc < 0) {
		// Fork failed
		fprintf(stderr, "Failed forking\n");
		exit(1);
	} else if (rc == 0)
		strcpy(process_name, "Child\n\0");
	else
		strcpy(process_name, "Parent\n\0");

	// Demonstrate writing to the File Descriptor simultaneously
	for (int i = 0; i < 50; ++i)
		write(fd, process_name, strlen(process_name));

	/*
	 * When two processes executing concurrently write to the same file
	 * simualtenously, their writes with overlap with eachother. This is
	 * for the same reason that two concurrently executing processes can
	 * write simualtenously to the shell. Due to the interleaving between
	 * both processes, their writes will be intertwined with eachother.
	 */
	return 0;
}
