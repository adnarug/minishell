/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:57:45 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/31 12:42:46 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strdup(const char *s1)
{
	char				*p_copy_s1;
	size_t				i;

	p_copy_s1 = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!p_copy_s1)
		return (NULL);
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
