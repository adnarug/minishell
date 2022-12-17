/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:06:37 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:25:27 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	pipe_last_cmd(t_minishell *data)
{
	if (data->exec->is_builtin == true)
		exec_last_builtin(data);
	else
	{
		if (create_fork(data) < 0)
			return ;
		else
			data->last_pid = data->pid;
		if (data->pid == 0)
		{
			signals_child_process(&data->termios_default);
			redirect_last_cmd(data);
			exec_bash_cmd(data);
		}
	}
	reset_stdin_stdout(data);
}

void	pipe_transitory_cmd(t_minishell *data)
{
	if (create_pipe(data) < 0)
		return ;
	if (data->prs_error == true)
	{
		redirect_stdin_to_pipe(data);
		return ;
	}
	if (data->exec->is_builtin == true)
		exec_transitory_builtin(data);
	else
	{
		if (create_fork(data) < 0)
			return ;
		if (data->pid == 0)
		{
			signals_child_process(&data->termios_default);
			redirect_transitory_cmd(data);
			exec_bash_cmd(data);
		}
		if (data->pid > 0)
			signals_child_process(&data->termios_default);
		redirect_stdin_to_pipe(data);
	}
}
