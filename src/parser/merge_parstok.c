/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_parstok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:24:58 by fnieves           #+#    #+#             */
/*   Updated: 2022/12/13 14:26:40 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_sublist_prs_tok	*del_cmd_parsdlist(t_sublist_prs_tok *sublist, \
					t_prs_tok **runner)
{
	t_prs_tok	*current;
	t_prs_tok	*delete;
	int			nb_nod_cmd;

	nb_nod_cmd = 0;
	current = (*runner)->next;
	delete = current;
	(*runner)->next = NULL;
	while (current)
	{
		current = current->next;
		free_parsed_tok(delete);
		delete->next = NULL;
		free(delete);
		delete = current;
		nb_nod_cmd += 1;
	}
	sublist->number_cmd = 1;
	sublist->size_sublist = sublist->size_sublist - nb_nod_cmd + 1;
	return (sublist);
}

/*
	Creamos el nuevo nodo, con el array total de comandos
	y destruimos la parte de la lista antigua partir del 
	primer parsed token command. El nuevo nodo lo añadimos al
	final de la lista.
*/

t_sublist_prs_tok	*new_parsdtk_cmd(t_sublist_prs_tok *sublist, \
					t_prs_tok **current, char **new_array_cmd)
{
	t_prs_tok	*parsedtok_cmd;
	t_prs_tok	*last;

	parsedtok_cmd = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_cmd)
		return (NULL);
	parsedtok_cmd->type = COMMAND;
	parsedtok_cmd->word = NULL;
	parsedtok_cmd->next = NULL;
	parsedtok_cmd->cmd_flags = new_array_cmd;
	sublist = del_cmd_parsdlist(sublist, current);
	last = find_last_parsedtok(sublist);
	last->next = parsedtok_cmd;
	return (sublist);
}

/*
	Creates the new array to attach to the new node with the
	total commands.
*/
char	**create_array_cmd(t_prs_tok *runner, int nb)
{
	char		**new_array_cmd;
	int			i;

	i = 0;
	new_array_cmd = (char **)malloc(sizeof(char *) * \
				(nb + 1));
	if (!new_array_cmd)
		return (NULL);
	nb = 0;
	while (runner)
	{
		i = 0;
		while (runner->cmd_flags[i])
		{
			new_array_cmd[nb] = ft_strdup(runner->cmd_flags[i]);
			nb += 1;
			i += 1;
		}
		runner = runner->next;
	}
	new_array_cmd[nb] = NULL;
	return (new_array_cmd);
}

/*
	Count how many commands there are in all the command nodes
	to malloc the final array comand of the single command node.
	Receives the first node with command.
	It returns the array with all the commands from all nodes.
*/
char	**count_commands(t_prs_tok *current)
{
	int			nb;
	int			i;
	char		**new_array_cmd;
	t_prs_tok	*runner;

	runner = current;
	nb = 0;
	while (current)
	{
		i = -1;
		while (current->cmd_flags[++i])
			nb = nb + 1;
		current = current->next;
	}
	new_array_cmd = create_array_cmd(runner, nb);
	return (new_array_cmd);
}

/*
	This function will convert all the nodes
	commands already placed at the end of the 
	list, into 1 single command node.
	It will be executed if and only if :
	- There is more than one node.
	- There is at least 1 command node.
	It will also be executed if all the nodes 
	are command nodes, and even if the list has
	not been sorted in that case.(*)no need to be sorted
	in that case.
*/
t_sublist_prs_tok	*merge_parstk_comm(t_sublist_prs_tok *sublist)
{
	t_prs_tok	*current;
	t_prs_tok	*prev;
	char		**new_array_cmd;

	current = sublist->prs_tok;
	prev = current;
	while (current)
	{
		if (current->type == COMMAND)
		{
			new_array_cmd = count_commands(current);
			sublist = new_parsdtk_cmd(sublist, &prev, new_array_cmd);
			break ;
		}
		prev = current;
		current = current->next;
	}
	return (sublist);
}
