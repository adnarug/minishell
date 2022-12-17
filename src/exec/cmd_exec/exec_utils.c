/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:57:54 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:45:30 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	reset_params(t_minishell *data)
{
	data->prs_error = false;
	data->ex_error = false;
	data->exec->is_builtin = false;
	data->exec->no_cmd = false;
	data->curr_fd_in = STDIN_FILENO;
	data->curr_fd_out = STDOUT_FILENO;
}

void	dup_stdin_and_stdout(t_minishell *data)
{
	data->std_in = dup(STDIN_FILENO);
	if (!data->std_in)
	{
		free(data->exec);
		exit (EXIT_FAILURE);
	}
	data->std_out = dup(STDOUT_FILENO);
	if (!data->std_out)
	{
		free(data->exec);
		exit (EXIT_FAILURE);
	}
}

void	reset_stdin_stdout(t_minishell *data)
{
	dup2(data->std_in, STDIN_FILENO);
	dup2(data->std_out, STDOUT_FILENO);
}

void	catch_exit_code(t_minishell *data)
{
	int	i;
	int	status;
	int	pid_check;

	i = 0;
	status = g_glob_var_exit;
	while (i < data->number_pipes + 1)
	{
		pid_check = waitpid(0, &status, 0);
		if (status != 0)
			reset_stdin_stdout(data);
		if (pid_check == data->last_pid)
		{
			if (WIFEXITED(status))
				g_glob_var_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_glob_var_exit = WTERMSIG(status);
		}
		i++;
	}
}

void	close_fds_in_out(t_minishell *data)
{
	if (data->curr_fd_in != STDIN_FILENO)
		close(data->curr_fd_in);
	if (data->curr_fd_out != STDOUT_FILENO)
		close(data->curr_fd_out);
}
