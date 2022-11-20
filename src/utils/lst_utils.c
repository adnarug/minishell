/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:14:36 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/20 13:57:19 by pguranda         ###   ########.fr       */
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

t_env	*ft_lstnew_env(char *key, char	*value)
{
	t_env		*node;

	node = malloc(sizeof(t_env));
	node->key = key;
	node->value = value;
	node -> next = NULL;
	return (node);
}

void	ft_lst_free(t_env *lst)
{
	t_env	*pointer;

	pointer = NULL;
	// printf("Before free %s", lst->key);
	
	while (lst != NULL)
	{
		pointer = lst->next;
		free(lst->key);
		lst->key = NULL;
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
		return NULL;
	while (head->next != node_to_find && head != NULL)
		head = head->next;
	return (head);
}

void	ft_lstdelone_env(t_env *node_to_delete, t_env *env)
{
	t_env	*previous_node;

	previous_node = ft_lst_find_previous(env, node_to_delete);
	if (node_to_delete == NULL || env == NULL)
		return ; // exit value
	previous_node->next = node_to_delete->next;
	// printf("***********NEXT:%s\n", node_to_delete->next);
	free(node_to_delete->key);
	node_to_delete->key = NULL;
	// free (node_to_delete->value);
	// node_to_delete->value = NULL;
	free(node_to_delete);
	node_to_delete = NULL;
	// print_env_lst(env);
}

t_env	*ft_lst_find(t_env *node, char *key)
{
	t_env	*tmp;
	
	tmp = node;
	if (tmp == NULL || key == NULL)
		return NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp -> next;
	}
	return (tmp);
}

void	print_env_lst_export(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
// Temp functions for testing TO BE DELETED
void	print_env_lst(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}