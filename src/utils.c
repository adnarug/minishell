/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:54:13 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/17 13:18:40 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**dup_matrix(char **matrix)
{
	int		i;
	char	**duplicate_matrix;

	i = 0;
	if (matrix == NULL || *matrix == NULL)
		return (NULL); // exit code?
	duplicate_matrix = malloc(sizeof(char *) * count_strings(matrix));
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
}