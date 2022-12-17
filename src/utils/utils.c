/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:54:13 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 20:16:56 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**dup_env_matrix(char **matrix)
{
	int		i;
	char	**duplicate_matrix;

	i = 0;
	if (matrix == NULL || *matrix == NULL)
		return (NULL);
	duplicate_matrix = malloc(sizeof(char *) * (count_strings(matrix) + 1));
	if (duplicate_matrix == NULL)
		return (NULL);
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

	i = 0;
	while (table[i] != NULL)
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
	table = NULL;
}

// Temp functions for testing 
void	print_2d(char **array)
{
	int	i;

	i = 0;
	if (array == NULL || array[i] == NULL)
	{
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
int	ft_strcmp(const char *str1, const char *str2)
{
	const unsigned char	*buf1;
	const unsigned char	*buf2;

	buf1 = (const unsigned char *)str1;
	buf2 = (const unsigned char *)str2;
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
