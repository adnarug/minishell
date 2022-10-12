/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:57:45 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/21 17:20:58 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strdup(const char *s1)
{
	char				*p_copy_s1;
	size_t				i;

	p_copy_s1 = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	i = 0;
	if (p_copy_s1 == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		p_copy_s1[i] = *s1;
		s1++;
		i++;
	}
	p_copy_s1[i] = '\0';
	return (p_copy_s1);
}
