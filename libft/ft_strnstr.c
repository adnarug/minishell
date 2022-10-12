/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:57:55 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/18 13:22:14 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t				i;
	size_t				z;
	size_t				temp_len;

	i = 0;
	z = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len > 0)
	{
		temp_len = len;
		while (haystack[i] == needle[z] && temp_len > 0)
		{
			i++;
			z++;
			if (needle[z] == '\0')
				return ((char *)&haystack[i - z]);
			temp_len--;
		}
		i = i - z + 1;
		z = 0;
		len--;
	}
	return (NULL);
}
