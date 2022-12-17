/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:14:36 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 18:59:18 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/*
	Initing nodes of my env:
	- key: USER
	- equal: =pguranda
	- value: pguranda, same pointer as equal, just +1 char
*/
t_env	*ft_lstnew_env(char *key, char	*eq_value)
{
	t_env		*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->key = key;
	if (eq_value != NULL)
	{
		node->equal = eq_value;
		node->value = eq_value;
	}
	else
		return (NULL);
	node->next = NULL;
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
		free(lst->value);
		lst->value = NULL;
		free(lst);
		lst = NULL;
		lst = pointer;
	}
	free(pointer);
	pointer = NULL;
}

t_env	*ft_lst_find_previous(t_env *head, t_env *node_to_find)
{
	if (head == NULL || node_to_find == NULL)
		return (NULL);
	while (head->next != node_to_find && head != NULL)
		head = head->next;
	return (head);
}
