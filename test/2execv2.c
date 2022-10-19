#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *const argv2[] = {"prog5", "abced", "ghij", NULL};
	printf("Antes: %s: %i \n", argv[0], getpid());
	// for (int i = 0; i < argc; i++)
	// {
	// 	printf("argumento %d: %s \n", i , argv[i]);
	// }
	execv("./prog32", argv2);
	printf("errror\n");
	return (-1);
}