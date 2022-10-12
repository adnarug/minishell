/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:28:50 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/02 12:01:48 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char				z;
	int					len;

	z = c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == z)
			return ((char *)s + len);
		len--;
	}
	return (0);
}
