/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:54:13 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/15 17:09:30 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**find_path(char **envp, char *key)
{
	char	*path;
	int		i;
	char	**path_to_builtins;

	path = NULL;
	i = 0;
	if (envp == NULL || *envp == NULL)
		return (NULL);
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = envp[i];
	path_to_builtins = ft_split(path + 5, ':');
	return (path_to_builtins);
}

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
// Temp utils
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

void	ft_lstadd_back_mini(t_env **lst, t_env *new)
{
	t_env				*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL )
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_mini(*lst);
	last -> next = new;
}

t_env	*ft_lstlast_mini(t_env *lst)
{
	t_env	*c;

	if (lst == NULL)
		return (NULL);
	c = lst;
	while (c->next != NULL)
		c = c->next;
	return (c);
}

void	print_env_lst(t_env *env_lst)
{
	while (env_lst != NULL)
	{
		printf("%s=", env_lst->key);
		printf("%s\n", env_lst->value);
		env_lst = env_lst->next;
	}
}

t_env	*ft_lstnew_env(char *value, char *key)
{
	t_env		*node;

	node = malloc(sizeof(t_env));
	node -> key = key;
	node -> value = value;
	node -> next = NULL;
	return (node);
}


