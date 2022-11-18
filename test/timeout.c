#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


int i;
void	timeout_hanlder(int unused)
{
	(void)(unused);
	printf("funcion unused\n");
}

int	t_getnum(int timeout)
{
	int n;
	char line[100];
	struct sigaction action;

	//i = 0;
	action.sa_handler = timeout_hanlder;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGALRM, &action, NULL);
	alarm(timeout);
	n = read(0, line, 100);
	alarm(0);
	if (n == -1 && errno == EINTR)
		return -1;
	n = atoi(line);
	return n;
}

int main ()
{
	int num;

	i = 0;
	while (1)
	{
		if ((num = t_getnum(3)) == -1)
			printf("time out\n");
		else
			printf("has introducdico %d\n", num);
		printf("ha pasado el segundo %d\n", i++);
	}
	return(0);
}