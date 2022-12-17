/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:07:29 by fnieves           #+#    #+#             */
/*   Updated: 2022/12/10 16:16:22 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *buff, char c)
{
	char	*new_buff;
	int		i;

	new_buff = malloc(sizeof(char) * (ft_strlen(buff) + 2));
	if (!new_buff)
		return (NULL);
	i = 0;
	if (buff)
	{
		while (buff[i])
		{
			new_buff[i] = buff[i];
			i++;
		}
	}
	new_buff[i] = c;
	new_buff[i + 1] = '\0';
	free(buff);
	buff = NULL;
	return (new_buff);
}
