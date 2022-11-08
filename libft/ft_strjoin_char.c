/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:07:29 by fnieves           #+#    #+#             */
/*   Updated: 2022/11/08 16:19:55 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h> //quitar
char *ft_strjoin_char(char *buff, char c) //poner esta en libft
{
	char *new_buff;
	int i;

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
	//printf("here, char = %c\n", c);
	//esto y el de abajo no hacen nada. Estamos liberando un valor de manera local, habria que pasar la direccion  de &buff
	free(buff); 
	buff = NULL; //quitar 
	return (new_buff);
}
