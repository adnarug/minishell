/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:33:30 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/01 19:18:45 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
hay que apuntar a null , despues de hacer un free. es  una buna practica para no tener que liarla 
por hacer 2 free al mismo pointer
Tengo que hacer free a los strings maloqueados de la lista de tokens, y de los parsed tokens??
grep hi -l >> '$USER' | wc -w > $HOME
*/

/*
	From general struct t_minishell, we start deleting 
	each sublist (pipe), from the array.
	We call the fucntion free_list_parsedtok, for each 
	sublist of nodes. After we also free the array of pipes.
	All strings will point to NULL after be free.
	After free, the list of parsed tokens, we will 
	also free the list of tokens.
*/
void	del_parsedtk_and_list_tok(t_minishell *data)
{
	int i = 0;
	while (data->array_sublist[i])
	{
		free_list_parsedtok(data->array_sublist[i]);
		i++;
	}
	free(data->array_sublist);
	data->array_sublist = NULL;
	//delete_list(&data->list);
}

/*
	It will run throght each parsed node , commands or redirect,
	of the list and and delete them. 
*/

void free_list_parsedtok(t_sublist_prs_tok *sublist)
{
	t_prs_tok	*current;
	t_prs_tok	*delete;
	
	if (!sublist)
		return ;
	current = sublist->prs_tok;
	delete = current;
	while(current)
	{
		current = current->next;
		free_parsed_tok(delete);
		delete = current;
	}
	//free(sublist->exec_path);
	//sublist->exec_path = NULL;
}

/*
	Inside each node, free , the words for redirecc
	and the whole array of commands.
*/
void free_parsed_tok(t_prs_tok	*delete)
{
	int i;
	

	free(delete->word);
	delete->word = NULL;
	if (delete->cmd_flags)
	{
		i = 0;
		while (delete->cmd_flags[i])
		{
			free(delete->cmd_flags[i]);
			delete->cmd_flags[i] = NULL;
			i++;
		}
		free(delete->cmd_flags);
		delete->next = NULL;	
	}

}
