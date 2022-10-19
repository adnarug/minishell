#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	//char *const argv2[] = {"prog2", "abced", "ghij", NULL};
	printf("Programa1: %s: %i \n", argv[0], getpid());
	for (int i = 0; i < argc; i++)
	{
		printf("argumento %d: %s \n", i , argv[i]);
	}
	return (0);
}