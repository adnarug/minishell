/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:54:13 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/01 16:46:48 by fnieves-         ###   ########.fr       */
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


//printitin list felipe . to be deleted
void	print_list(t_list_token *list)
{
	t_nod_token	*temp;
	int i = 0;
	if (!list)
	{
		printf("List does not exist which does not mean is leer\n");
		return;
	}
	if (!list->head)
	{
		printf("List exists but with no nodes\n");
		return;
	}
	temp = list->head;
	printf("-------Informacion de La lista----------\n");
	while(temp)
	{
		if (temp->simple_quote )
			printf("Elemnto: %i, valor= %s, tipo = %c, single quote ON =%i \n",i ,temp->name, temp->flag, temp->simple_quote);
		else if (temp->double_quote)
			printf("Elemnto: %i, valor= %s, tipo = %c, double quot ON =%i \n",i ,temp->name, temp->flag, temp->double_quote);
		else
			printf("Elemnto: %i, valor= %s, tipo = %c. No single/double quote \n",i ,temp->name, temp->flag);
		i++;
		temp = temp->next;
	}
	printf("-------END  IMPRESION  lista-------\n");
}

void print_token(t_nod_token	*token)
{
	if (!token)
	{
		printf("token apunta  anull\n");
		return;
	}
	printf("-------imprimirmpos valores det oken----------\n");
	printf("el valor de name: %s\n", token->name);
	printf("-------END  IMPRESION  TOKEN-------\n");

}