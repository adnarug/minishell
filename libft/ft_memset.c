/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:40:22 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/01 10:42:47 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char				*p;

	p = b;
	while (len > 0)
	{
		*p = c;
		p++;
		len--;
	}
	return (b);
}
