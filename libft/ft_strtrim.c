/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:35:22 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/19 15:31:37 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_trim_front(char const *s1, char const *set);
unsigned int	ft_trim_back(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ptr;
	size_t		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 != '\0' && ft_strchr(set, *s1))
		++s1;
	len = ft_strlen (s1);
	if (len > 0)
	{
		while (ft_strchr(set, s1[len - 1]))
		--len;
	}
	ptr = malloc (sizeof (char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy (ptr, s1, len +1);
	return (ptr);
}
