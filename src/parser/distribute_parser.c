/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:44:56 by fnieves           #+#    #+#             */
/*   Updated: 2022/12/13 18:57:25 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	only if we have 2 parsed token: first command and second redir
	We put command at the end.
*/
void	send_end_node(t_sublist_prs_tok **sublist,
		t_prs_tok **current, t_prs_tok **prev)
{
	t_prs_tok	*second;
	t_prs_tok	*last;

	last = find_last_parsedtok(*sublist);
	second = (*current)->next;
	(*prev)->next = second;
	last->next = (*current);
	last = (*current);
	(*current)->next = NULL;
	(*current) = second;
}

t_sublist_prs_tok	*reorder_nofirst(t_sublist_prs_tok *sublist)
{
	t_prs_tok	*current;
	t_prs_tok	*prev;

	current = sublist->prs_tok;
	while (sublist->number_cmd)
	{
		if (current->type == COMMAND)
		{
			sublist->number_cmd--;
			send_end_node(&sublist, &current, &prev);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (sublist);
}

t_sublist_prs_tok	*reorder_first(t_sublist_prs_tok *sublist)
{
	t_prs_tok	*second;
	t_prs_tok	*last;
	t_prs_tok	*first;

	while (sublist->prs_tok->type == COMMAND && sublist->number_cmd)
	{
		first = sublist->prs_tok;
		last = find_last_parsedtok(sublist);
		second = first->next;
		sublist->prs_tok = second;
		last->next = first;
		first->next = NULL;
		sublist->number_cmd--;
	}
	return (sublist);
}

/*
	we put commands to the end of the sublist.
	At  least we have 2 elements in the sublist
	If sublist hast just one command node and its 
	at the end (sorted), it will not execute and return.
*/
t_sublist_prs_tok	*reorder(t_sublist_prs_tok *sublist)
{
	t_prs_tok	*last;

	last = find_last_parsedtok(sublist);
	if (sublist->number_cmd == 1 && last->type == COMMAND)
		return (sublist);
	sublist = reorder_first(sublist);
	sublist = reorder_nofirst(sublist);
	return (sublist);
}

/*
	We will not sort the sublist except for 4 cases:
	There are not any parsed token or just one parsed token.
	All parse tokens are type COMMAND, so no need to sort,
	or no commands at all.
	1er comando > redir1 2o comando >> redir2
	
*/

void	ft_distribute_parse(t_minishell *data)
{
	int	i;

	i = 0;
	if (!data->array_sublist)
		return ;
	while (data->array_sublist[i])
	{
		if (data->array_sublist[i]->size_sublist > 1 \
			&& data->array_sublist[i]->number_cmd)
		{
			if (data->array_sublist[i]->number_cmd != \
				data->array_sublist[i]->size_sublist)
			{
				data->array_sublist[i] = reorder(data->array_sublist[i]);
				data->array_sublist[i] = \
				merge_parstk_comm(data->array_sublist[i]);
			}
		}
		i++;
	}
}
