/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:11 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/14 11:56:07 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*p_s;
	int					i;
	int					len;

	p_s = NULL;
	i = 0;
	len = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	p_s = (char *)malloc(sizeof(char) * len);
	if (p_s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		p_s[i] = (*f)(i, s[i]);
		i++;
	}
	p_s[i] = '\0';
	return (p_s);
}
