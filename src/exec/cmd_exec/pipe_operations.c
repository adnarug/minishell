/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:06:37 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/03 15:45:15 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 0
#include "../../../include/minishell.h"

void	pipe_last_cmd(t_minishell *data)
{
	// if (data->exec->no_cmd == true || data->prs_error == true)
	// {
	// 	reset_stdin_stdout(data);
	// 	if (data->prs_error == true)
	// 		// g_exit_code = EXIT_FAILURE;
	// 	return ;
	// }
	if (data->exec->is_builtin == true)
		exec_last_builtin(data);
	else
	{
		if (create_fork(data) < 0)
			return ;
		if (data->pid == 0)
		{
			signals_child_process(&data->termios_default);
			// printf("fdin: %d fdout: %d pid:%d stdin:%d\n", data->std_in, data->std_out, data->pid, STDIN_FILENO);
			redirect_last_cmd(data);
			if (DEBUG == 1)
				printf("*******Executing the last command\n");
			exec_bash_cmd(data);
		}
	}
	reset_stdin_stdout(data);
}

void	pipe_transitory_cmd(t_minishell *data)
{

	if (create_pipe(data) < 0)
		return ;
	// if (data->prs_error == true)
	// {
	// 	redirect_stdin_to_pipe(data);
	// 	return ;
	// }
	if (data->exec->is_builtin == true)
	{
		if (DEBUG == 1)
			printf("coming to execute builtin: %s\n", data->exec->cmd_flags[0]);
		exec_transitory_builtin(data);
	}
	else
	{
		if (create_fork(data) < 0)
			return ;
		if (data->pid == 0)
		{
			if (DEBUG == 1)
				printf("*******Trans comand\n");
			signals_child_process(&data->termios_default);
			redirect_transitory_cmd(data);
			exec_bash_cmd(data);
		}
		if ( data->pid > 0)
			signals_child_process(&data->termios_default);
		redirect_stdin_to_pipe(data);
	}
}