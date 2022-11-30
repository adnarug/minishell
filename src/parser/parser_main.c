/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/30 18:22:42 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*\
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
< test2 grep hi | wc -w > test2_result

*/

/*
< test2 < tedt3 grep hi >> '$USER' | wc -w > $HOME | echo >> $? | cd "$USER" $$ << $
 grep hi -l >> '$USER' | wc -w > $HOME | echo >> $? | cd "$USER" $$ "'$USER'"  << $

 grep hi | wc 
*/

void ft_parser(t_minishell *data)
{
	t_nod_token *current ;//to run throug list of  tokens not parsed
	int i;

	i = 0;
	if (!data->list.head) //we had no input and/or the list of tokens is empty
	{
		printf("no tokens to parse\n");
		return ;
	}
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
		// if (data->array_sublist[i]->number_cmd != 1)
		// {
		// 	printf("the pipe %i has more/less than 1 command\n", i);
		// 	exit(2);
		// }
		if (!data->array_sublist[i])
		{
			printf("Error allocting sublist pared token\n");
			exit(3);
		}
		i++;
	}
	data->array_sublist[i] = NULL;
}
