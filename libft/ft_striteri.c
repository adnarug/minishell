/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:15:52 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/21 17:30:04 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int				i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		(*f)(i, s + i);
		i++;
	}
	return ;
}
