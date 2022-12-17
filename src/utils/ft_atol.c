/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:39:22 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/10 16:29:08 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

long long	ft_atol(const char *str, bool *error)
{
	int				i;
	long long		result_integer;
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
	if (((result_integer * sign) > 9223372036854775807) || \
	((result_integer * sign) < -922337203685477589))
	{
		*error = true;
		return (255);
	}
	return (result_integer * sign);
}
