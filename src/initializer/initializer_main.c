/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:07:04 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 16:28:35 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initializer_data_error(t_minishell *data)
{
	data->input_error = false;
	data->prs_error = false;
	data->lx_error = false;
	data->ex_error = false;
	data->exit_minishell = false;
}

void	initializer_data(t_minishell *data)
{
	g_glob_var_exit = 0;
	data->line = NULL;
	data->list.head = NULL;
	data->list.size = 0;
	data->array_sublist = NULL;
	data->number_pipes = 0;
	initializer_data_error(data);
	tcgetattr(STDOUT_FILENO, &data->termios_default);
}
