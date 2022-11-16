#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>



typedef struct s_all
{
	int number;
}				t_all;

t_all *all_data(void)
{
	static t_all data;
	return &data;
}

void handler(int sigum)
{
	printf("signal %d received. Counter reset\n", sigum);
	all_data()->number = 0;
}



int main()
{
	int n;

	// n = 0;
	all_data()->number = 0;
	//global_i = 0;
	signal(SIGINT, &handler);
	//signal(SIGQUIT, SIG_IGN);
	//signal(SIGTERM, SIG_IGN); 
	while (1)
	{
		//printf("pasa segundo %d\n", n++);
		printf("pasa segundo %d\n", all_data()->number++);
		sleep(1);
	}
	printf("pasa segundo %d\n", n);
	return(0);
}


int global_i;

int handler2(int signum)
{
	int i;

	i = 0;
	printf("signal %d received. Counter reset\n", signum);
	return (i);
}

void handler3(int signum)
{
	global_i = 0;
	printf("signal %d received. Counter reset\n", signum);
}