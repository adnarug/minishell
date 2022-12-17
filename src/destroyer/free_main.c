/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:03:09 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/13 11:38:02 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all(t_minishell *data)
{
	del_array_list_prsdtok(data);
	delete_list(&data->list);
}

void	free_all_exec(t_minishell *data)
{
	ft_lst_free(data->env_lst);
	ft_free_2d(data->env_argv);
}

void	free_loop_exec(t_minishell *data)
{
	free(data->hdoc->hdocs_nodes);
	data->hdoc->hdocs_nodes = NULL;
	free(data->hdoc);
	data->hdoc = NULL;
	free(data->exec);
	data->exec = NULL;
}
