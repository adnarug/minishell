/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:06:04 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/21 17:09:58 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define LONG_MIN -2147483648

static int		ft_count_digits(int n);
static char		*ft_allocation(int n, char *s);

char	*ft_itoa(int n)
{
	char				*s;

	if (n == LONG_MIN)
	{
		s = (char *)(malloc(12));
		ft_strlcpy(s, "-2147483648", 12);
		return (s);
	}
	s = (char *)malloc((ft_count_digits(n) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s = ft_allocation(n, s);
	return (s);
}

static int	ft_count_digits(int n)
{
	int				counter;

	counter = 0;
	if (n < 0)
	{
		counter++;
		n *= -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		counter++;
	}
	counter++;
	return (counter);
}

static char	*ft_allocation(int n, char *s)
{
	int				digit;
	int				len;

	digit = 0;
	len = ft_count_digits(n);
	s[len] = '\0';
	len--;
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	while (n >= 10)
	{
		digit = n % 10;
			s[len] = digit + '0';
			len--;
			n = n / 10;
	}
	s[len] = n + '0';
	return (s);
}
