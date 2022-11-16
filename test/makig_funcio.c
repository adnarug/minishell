#include <stdio.h>
void ft_print()
{
	printf("hola mundo\n");
}

void ft_print2(int x)
{
	printf("ft_print2 has dicho %i\n", x);
}

int ft_print3(int x)
{
	printf("ft_print3: 2*%d=%d\n", x, 2*x);
	return (2*x);
}

int main()
{
	void(*funcion)(void);
	void(*funcion2)(int);
	int(*funcion3)(int);
	int x;

	x = 5;
	funcion = &ft_print;
	funcion2 = &ft_print2;
	funcion3 = &ft_print3;
	(*funcion)();
	funcion2(x);
	printf(" valor de retorno en main de ft3: %i \n", funcion3(x));
	//funcion();

	return 0;
}