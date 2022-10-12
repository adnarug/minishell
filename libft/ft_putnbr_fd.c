/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:45:26 by pguranda          #+#    #+#             */
/*   Updated: 2022/05/27 11:37:31 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define LONG_MIN -2147483648
#define LONG_MAX 2147483647

int	ft_putnbr_fd(int n, int fd, int counter)
{	
	static int	size;

	if (n > LONG_MAX || n < LONG_MIN)
		return (0);
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
