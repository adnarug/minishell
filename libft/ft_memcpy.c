/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:25:18 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/19 15:29:20 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char				*p_dst;
	const char			*p_src;

	p_dst = dst;
	p_src = src;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (n > 0)
	{
		*p_dst = *p_src;
		p_dst++;
		p_src++;
		n--;
	}
	return (dst);
}
