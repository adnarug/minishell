
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define READ_END    0    /* index pipe extremo escritura */
#define WRITE_END   1    /* index pipe extremo lectura */

int main()
{
	int fd1[2], fd2[2];
	int status, pid;

	pipe(fd1);
	pid = fork();
	if (pid == 0)
	{
		close(fd1[READ_END]);
		dup2(fd1[WRITE_END], STDOUT_FILENO);
		close(fd1[WRITE_END]);
		excelp("/bin/ls", "-ls", NULL);
	}
	else
	{
		close(fd1[READ_END]);
	}

}
