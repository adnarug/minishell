/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:52:34 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/19 16:13:08 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static int	ft_isnum(char c);
static int	ft_white_space(const char *c);

int	ft_atoi(const char *str)
{
	int				i;
	int				result_integer;
	int				sign;

	i = 0;
	result_integer = 0;
	sign = 1;
	i = ft_white_space(str);
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isnum(str[i]) == 1)
	{
		result_integer = result_integer * 10 + str[i] - '0';
		i++;
	}
	return (result_integer * sign);
}

static int	ft_white_space(const char *str)
{
	int				i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

static int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
