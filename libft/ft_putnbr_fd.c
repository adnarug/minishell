/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:45:26 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/19 19:08:08 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define LONG_MIN -2147483648
#define LONG_MAX 2147483647

/* He cambiad esta fincion par ano
tener problemas desde casa*/

int	ft_putnbr_fd(int n, int fd, int counter)
{	
	static int	size;

	if (n == -2147483648)
	{
		ft_putstr_fd("2147483648", fd);
		return (10);
	}
	if (n < 0)
	{
		n = n * -1;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		size = counter;
		return (1);
	}
	counter++;
	ft_putnbr_fd(n / 10, fd, counter);
	ft_putchar_fd((n % 10) + '0', fd);
	return (size + 1);
}
