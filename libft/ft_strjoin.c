/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:00:12 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/09 14:07:57 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char					*new_string;
	unsigned int			len;
	int						i;
	int						counter;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc(sizeof(char) * (len + 1));
	counter = 0;
	i = 0;
	if (!new_string)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new_string[i] = s1[i];
		i++;
	}
	while (counter <= ft_strlen(s2))
	{
		new_string[i] = s2[counter];
		i++;
		counter++;
	}
	return (new_string);
}
