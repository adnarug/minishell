/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/02 15:09:37 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*\
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
< test2 grep hi | wc -w > test2_result

*/

/*
< test2 < tedt3 grep hi >> '$USER' | wc -w > $HOME | echo >> $? | cd "$USER" $$ << $
 grep hi -l >> '$USER' | wc -w > $HOME | echo >> $? | cd "$USER" '"'$USER'"' "'$USER'" $$  << $

 grep hi | wc 
 short this function
*/

/*
	It will check if a pipe has just 1 command.
	If it is not so, will not be executed, 
	and prompt again (return 0)
	returns 1 if number of commands is only 1.
	This function has to be executed after the heredocs.
	Pasha will need it.
*/
int	check_number_commds(t_minishell *data) //if pahs doesnt use it delet it
{
	int	i;
	
	i = -1;
	while (data->array_sublist[++i])
	{
		if (data->array_sublist[i]->number_cmd != 1)
		{
			printf("the pipe %i has more/less than 1 command\n", i); //add an error
			return (0);
		}
	}
	return (1);
}

void ft_parser(t_minishell *data)
{
	t_nod_token *current ;//to run throug list of  tokens not parsed
	int i;

	i = 0;
	data->prs_error = true;
	data->array_sublist = (t_sublist_prs_tok **)malloc(sizeof(t_sublist_prs_tok *) * (data->number_pipes + 2));
	if (!data->array_sublist)
	{
		printf("error malloc in the array of list\n");
		return ;
	}
	current = data->list.head;
	while (current)
	{
		data->array_sublist[i] = create_sublist(&current);
		if (!data->array_sublist[i])
		{
			printf("error malloc sublist pared token\n"); //i do not to take ito account the subproblems with memory. Here , is already checking
			exit(3);
		}
		i++;
	}
	data->array_sublist[i] = NULL;
	if (!data->prs_error)
		glob_var_exit = (EXIT_FAILURE);
}
