/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:14:36 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/17 13:18:01 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Util functions for working with t_env linked list*/
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

t_env	*ft_lstnew_env(char *value, char *key)
{
	t_env		*node;

	node = malloc(sizeof(t_env));
	node -> key = key;
	node -> value = value;
	node -> next = NULL;
	return (node);
}

void	ft_lst_free(t_env *lst)
{
	t_env	*pointer;

	pointer = NULL;
	while (lst != NULL)
	{
		pointer = lst->next;
		free(lst->key);
		lst->key = NULL;
		free(lst);
		lst = NULL;
		lst = pointer;
	}
	free (pointer);
	pointer = NULL;
}

// Temp functions for testing TO BE DELETED
void	print_env_lst(t_env *env_lst)
{
	while (env_lst != NULL)
	{
		printf("%s = %s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}