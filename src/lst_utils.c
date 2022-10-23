/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:14:36 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/20 17:53:06 by fnieves-         ###   ########.fr       */
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

// Felipe List functiones below:

/*
	Add a new token to the end of the list
*/
void add_toke_list(t_list_token *list, t_nod_token *new)
{
	t_nod_token	*last;
	
	if (!list) //List does not exist >>> return
		return;
	if (!list->head) //Empty list. Add token
	{
		list->head = new;
		return ;
	}
	last = find_last_node(list);
	last->next = new;
}

/*
	We create a node from the each word,
	separated by a space coming from promt.
	If there is any problem in the operation we return,
	a pointer to NULL
	Returns the pointer to the node.
*/
t_nod_token *create_tok(char *word_tok)
{
	t_nod_token *new_tok;
	
	new_tok = (t_nod_token *)malloc(sizeof(t_nod_token));
	if (!new_tok)
		return (NULL);
	new_tok->name = NULL; //do we need to inicializar a null the field word?
	new_tok->next = NULL;
	new_tok->name = ft_strdup(word_tok);
	if (!new_tok->name)
	{
		free(new_tok); //free . despues de free , se iguala new_tok = NULL?
		return (NULL);
	}
	return(new_tok);
}

t_nod_token *find_last_node(t_list_token *list)
{
	t_nod_token	*last;

	if (!list || !list->head)
		return (NULL);
	last = list->head;
	while (last->next)
		last = last->next;
	return (last);
}

void	delete_list(t_list_token *list)
{
	t_nod_token	*del;
	t_nod_token	*current;
	
	if (!list || !list->head)
		return ;
	del = list->head;
	while (del)
	{
		current = del->next;
		free(del->name);
		free(del);
		del = current;
	}
	list->head = NULL;
}
