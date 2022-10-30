#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd[2]; //f[0] lee, f[1]: write
	int x;
	
	if (pipe(fd) == -1)
	{
		printf("An error ocuurred with oppening the pipe \n");
		return 1;
	}
	int id = fork();
	if (id == 0)
	{
		close(fd[0]);
		printf("Input a number: \n");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	return (0);

}