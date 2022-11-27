/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:33:30 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/27 01:33:58 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_array_parsedtk(t_minishell *data)
{
	int i = 0;
	while (data->array_sublist[i])
	{
		free_list_parsedtok(data->array_sublist[i]);
		i++;
	}
	free(data->array_sublist);
}

void free_parsed_tok(t_prs_tok	*delete)
{
	int i;
	
	i = 0;
	free(delete->word);
	while (delete->cmd_flags[i])
	{
		free(delete->cmd_flags[i]);
		i++;
	}
	free(delete->cmd_flags);
	delete->next = NULL;
}


void free_list_parsedtok(t_sublist_prs_tok *sublist)
{
	t_prs_tok	*current;
	t_prs_tok	*delete;
	
	if (!sublist)
		return ;
	current = sublist->first_prs_tok;
	delete = current;
	while(current)
	{
		current = current->next;
		free_parsed_tok(delete);
		delete = current;
	}
	free(sublist->exec_path);
}