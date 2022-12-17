/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:53 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 14:04:05 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Add a new token to the end of the list
*/
void	add_toke_list(t_list_token *list, t_nod_token *new)
{
	t_nod_token	*last;

	if (!list)
		return ;
	if (!list->head)
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

t_nod_token	*create_tok(t_lexing *lex_struct)
{
	t_nod_token	*new_tok;

	new_tok = (t_nod_token *)malloc(sizeof(t_nod_token));
	if (!new_tok)
		return (NULL);
	new_tok->next = NULL;
	new_tok->name = lex_struct->buff;
	new_tok->flag = lex_struct->type;
	return (new_tok);
}

t_nod_token	*find_last_node(t_list_token *list)
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
		del->name = NULL;
		free(del);
		del = NULL;
		del = current;
	}
	list->head = NULL;
}
