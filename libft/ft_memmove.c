/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:52:08 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/01 11:46:19 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char				*p_dst;
	const char			*p_src;
	unsigned int		i;

	i = 0;
	p_dst = dst;
	p_src = src;
	if (src > dst)
	{
		while (n > i)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	else if (src < dst)
	{
		while (n > 0)
		{
			p_dst[n - 1] = p_src[n - 1];
			n--;
		}
	}
	return (dst);
}
