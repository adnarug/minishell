/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:28:50 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/19 16:21:02 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strchr(const char *s, int c)
{
	char				z;
	const char			*p_c;

	z = c;
	p_c = s;
	while (*p_c != '\0' || z == '\0')
	{
		if (*p_c == z)
			return ((char *)p_c);
		p_c++;
	}
	return (NULL);
}
