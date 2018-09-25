#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
 * CMPT360 Lab 2
 * Cooper Wallace
 *
 * Question 1
 * Write a program that calls fork(). Before calling fork(), have the main
 * process access a variable (e.g., x) and set its value to something
 * (e.g., 100). What value is the variable in the child process? What
 * happens to the variable when both the child and parent change the
 * value of x?
 */

int main(int argc, char *argv[])
{
	int x = 100; // Declare the Variable X before calling fork()

	/* When we fork a process, the child process will get its own
	 * duplicate of the address space. This means that both the Parent
	 * and Child will have their own instance of variable 'x'
	 *
	 * Any modifications to 'x' will only shown up in that process.
	 */

	int rc = fork(); // Fork the Process

	if (rc < 0) {
		// Fork failed
		fprintf(stderr, "Failed forking\n");
		exit(1);
	} else if (rc == 0) {
		// Child process
		printf("The Child process has a 'x' value of: %d\n", x);
		x = 120; // Change the 'x' variable to demonstrate it only
			 // changes in the Child process
		printf("The Child process has a new 'x' value of: %d\n", x);
	} else {
		// Parent process shall wait until its Child has terminated
		// to show seperate instances of the 'x' variable.
		int wc = wait(NULL);

		printf("The Parent process has a 'x' value of: %d\n", x);

		// As we can see the value of 'x' in the Parent process has
		// not changed, even though we changed it in the Child.
		// This is because both processes have a seperate address
		// space

		x = 921;
		printf("The Parent process has a new 'x' value of: %d\n", x);
	}


	return 0;
}
