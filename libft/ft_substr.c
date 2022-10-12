/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:23 by pguranda          #+#    #+#             */
/*   Updated: 2022/05/10 12:04:59 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_string;
	unsigned int	i;

	i = 0;
	if (s == NULL )
		return (NULL);
	if (len > (size_t)ft_strlen(s))
		len = (size_t)ft_strlen(s);
	if (start > (unsigned int)ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	sub_string = (char *)(malloc((len + 1) * sizeof(char)));
	if (sub_string == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		sub_string[i] = s[start];
		i++;
		start++;
	}
	sub_string[i] = '\0';
	return (sub_string);
}
