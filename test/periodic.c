#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
 #include <fcntl.h>


char *p, buffer[10000];

void 	handler()
{
	int fd;

	fd = open("buffer.save", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd, buffer, p-buffer);
	close(fd);
	alarm(10);
}


int main ()
{
	int count;

	struct sigaction action;
	p = buffer;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &action, NULL);
	alarm(10);
	while ((count = read(0, p, 200)))
	{
		p =  p + count ;
	}
	return(0);
}