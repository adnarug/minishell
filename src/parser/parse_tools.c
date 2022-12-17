/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:21:15 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/13 18:58:39 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_sublist_prs_tok	*create_sublist(t_minishell *data, t_nod_token **current)
{
	t_sublist_prs_tok	*sub_list_pars;

	sub_list_pars = (t_sublist_prs_tok *)malloc(sizeof(t_sublist_prs_tok));
	if (!sub_list_pars)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	sub_list_pars->prs_tok = NULL;
	sub_list_pars->size_sublist = 0;
	sub_list_pars->number_cmd = 0;
	sub_list_pars->exec_path = NULL;
	parsing_tokens(data, current, sub_list_pars);
	if (data->prs_error == false)
	{
		free(sub_list_pars);
		sub_list_pars = NULL;
		return (NULL);
	}
	return (sub_list_pars);
}

t_prs_tok	*find_last_parsedtok(t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*last;

	if (!sub_list_pars->prs_tok)
		return (NULL);
	last = sub_list_pars->prs_tok;
	while (last->next)
		last = last->next;
	return (last);
}

/*
  Add parsed tokens to sublits. It could be cmd parsed nodes. For array
  or redirecttion parsed nodes
*/
void	add_parsedtok_sublist(t_prs_tok *parsedtok,
		t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*last;

	if (!sub_list_pars)
		return ;
	if (!sub_list_pars->prs_tok)
	{
		sub_list_pars->prs_tok = parsedtok;
		return ;
	}
	last = find_last_parsedtok(sub_list_pars);
	last->next = parsedtok;
}

/*
	If in the list there is only parsed cpmmand.
	We will NOT need this function because the node
	will be already sorted and joined.
*/
t_sublist_prs_tok	*del_list_allprstk_sorted(t_sublist_prs_tok *sublist)
{
	t_prs_tok	*current;
	t_prs_tok	*delete;

	current = sublist->prs_tok;
	delete = current;
	while (current)
	{
		current = current->next;
		free_parsed_tok(delete);
		delete->next = NULL;
		free(delete);
		delete = current;
	}
	sublist->prs_tok = NULL;
	sublist->number_cmd = 1;
	sublist->size_sublist = 1;
	return (sublist);
}
