#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * CMPT360 Lab 2
 * Cooper Wallace
 *
 * Question 3
 * Write another program using fork(). The child process should print "hello";
 * the parent process should print “goodbye”. You should try to ensure that
 * the child process always prints first; can you do this without calling
 * wait() in the parent?
 */

int main(int argc, char *argv[])
{
	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "Failed forking\n");
		exit(1);
	} else if (rc == 0)
		printf("Hello\n");
	else {
		sleep(3);
		printf("Goodbye\n");
	}

	/*
	 * Rather than using the wait() function, we can make the parent
	 * process sleep for an arbitrary length of time. However, this
	 * does not guarentee that the parent process will execute after
	 * the child. For example; if the parent process was have 4 seconds
	 * on the CPU before the child process, then Goodbye will be printed
	 * before Hello.
	 *
	 * The second problem with using sleep() is that if the child process
	 * takes more time to execute than the specified time in the parent
	 * process, then they will execute out of order. Something that could
	 * occur as the code base grows.
	 */

	return 0;
}
