#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
 #include <errno.h>


void myhandler(int sigtype)
{
	printf("got signal %d\n", sigtype);
}

int main()
{
	struct sigaction action;
	int n, p[2];
	char buff[1000];
	int i = 0;

	pipe(p);
	action.sa_handler = myhandler;
	sigemptyset(&action.sa_mask);
	//action.sa_flags = SA_RESTART;
	action.sa_flags = 0;

	sigaction(SIGINT, &action, NULL);
	while (1)
	{
		n = read(p[0], buff, 1000);
		printf("read returned %d, errno = %d\n", n, errno);
		printf("pasa segundo %i \n", i++);
		sleep(1);
	}
	return 0;
}