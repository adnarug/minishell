/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/12 22:12:53 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	It will check if a pipe has just 1 command.
	If it is not so, will not be executed,
	and prompt again (return 0)
	returns 1 if number of commands is only 1.
	This function has to be executed after the heredocs.
	Pasha will need it.
*/
int	check_number_commds(t_minishell *data)
{
	int	i;

	i = -1;
	while (data->array_sublist[++i])
	{
		if (data->array_sublist[i]->number_cmd != 1)
		{
			printf("the pipe %i has more/less than 1 command\n", i);
			return (0);
		}
	}
	return (1);
}

void	ft_parser(t_minishell *data)
{
	t_nod_token	*current;
	int			i;

	i = 0;
	data->prs_error = true;
	data->array_sublist = (t_sublist_prs_tok **)
		malloc(sizeof(t_sublist_prs_tok *) * (data->number_pipes + 2));
	if (!data->array_sublist)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	current = data->list.head;
	while (current)
	{
		data->array_sublist[i] = NULL;
		data->array_sublist[i] = create_sublist(data, &current);
		if (data->prs_error == false)
			return ;
		if (!data->array_sublist[i])
			print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
		i++;
	}
	data->array_sublist[i] = NULL;
}
