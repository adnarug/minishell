/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:54:13 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/02 18:55:51 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**dup_env_matrix(char **matrix)
{
	int		i;
	char	**duplicate_matrix;

	i = 0;
	// if (matrix == NULL || *matrix == NULL)
	// 	return (NULL); // exit code?
	duplicate_matrix = malloc(sizeof(char *) * (count_strings(matrix) + 1));//protection
	// if (duplicate_matrix == NULL)
	// 	return NULL;
	while (matrix[i] != NULL)
	{
		duplicate_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	duplicate_matrix[i] = NULL;

	return (duplicate_matrix);
}

int	count_strings(char **array)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (array[i] != NULL)
	{
		i++;
		counter++;
	}
	return (counter);
}

void	ft_free_2d(char **table)
{
	int	i;
	size_t len;

	i = 0;
	len = count_strings(table);
	while (table[i] != NULL)
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
	table = NULL;
}

// Temp functions for testing TO BE DELETED
void	print_2d(char **array)
{
	int i;

	i = 0;
	if (array == NULL || array[i] == NULL)
	{
		printf("Trying to print an empty 2d\n");
		return ;
	}
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
	printf("%s\n", array[i]);
}

/* returns the value of the difference found in two strings, 0 if equal */
int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*buf1;
	const unsigned char	*buf2;

	buf1 = (const unsigned char *)s1;
	buf2 = (const unsigned char *)s2;
	if (*buf1 != *buf2)
		return (*buf1 - *buf2);
	while (*buf1 && *buf2)
	{
		if (*buf1 != *buf2)
			return (*buf1 - *buf2);
		buf1++;
		buf2++;
	}
	if (*buf1 == '\0' && *buf2 != '\0')
		return (0 - *buf2);
	else if (*buf2 == '\0' && *buf1 != '\0')
		return (*buf1);
	return (0);
}