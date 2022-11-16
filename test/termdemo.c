#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main()
{
	int status;
	int a, b , c;

	a = 1;
	b = 0;
	if(fork())
	{
		//Parent
		wait(&status);
		if(WIFEXITED(status))
			printf("soy el padre con ID: %d, Child exited normally with exit status %d\n",  getpid(), WEXITSTATUS(status));
		if(WIFSIGNALED (status))
		//else
			printf("Child exited on signal %d: %s\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
		
	}
	else
	{
		//Child
		printf("Child PID = %d\n", getpid());
		//*(int *)0 = 99;
		pause();
		for(int i = 0; i < 5; i++)
		{
			printf("pasa segundo %d\n", i);
			if (i == 3)
				c = a/b;
			sleep(1);
		}
		exit(11);
	}
	return(0);
}