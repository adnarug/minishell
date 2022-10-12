/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:06:53 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/19 15:43:08 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char					*p_s1;
	const unsigned char					*p_s2;
	int									diff;
	int									i;

	p_s1 = s1;
	p_s2 = s2;
	i = 0;
	if (p_s1 == p_s2)
		return (0);
	while (n > 0)
	{
		diff = p_s1[i] - p_s2[i];
		if (diff != 0)
			return (diff);
		n--;
		i++;
	}
	return (0);
}
