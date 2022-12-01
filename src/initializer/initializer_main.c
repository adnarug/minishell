/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:07:04 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/01 12:19:58 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void initializer_header_sublist(t_minishell *data)

void	initializer_data_error(t_minishell *data) //still any values to inicialze (could be done in the later functions but all variables must be inizialice)
{
	data->prs_error = true;
	data->lx_error = true;
	data->ex_error = true;
	data->exit_minishell = true;
}


void	initializer_data(t_minishell *data) //still any values to inicialze (could be done in the later functions but all variables must be inizialice)
{
	glob_var_exit = 0;
	data->line = NULL;
	data->list.head = NULL;
	data->list.size = 0;
	data->array_sublist = NULL;
	data->number_pipes = 0;
	initializer_data_error(data);
	
	// ask PAvel about the other all his var to inizialice
	tcgetattr(STDOUT_FILENO, &data->termios_default);

}