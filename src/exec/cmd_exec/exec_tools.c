/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:13:52 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:44:38 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_dup2(int fd_old, int fd_new)
{
	if (dup2(fd_old, fd_new) < 0)
	{
		perror(NULL);
		exit (EXIT_FAILURE);
	}
	close(fd_old);
}

int	create_pipe(t_minishell *data)
{
	if (pipe(data->pipe) < 0)
	{
		perror(NULL);
		exit(128);
	}
	return (0);
}

int	create_fork(t_minishell *data)
{
	signals_parent_process();
	data->pid = fork();
	if (data->pid < 0)
	{
		perror(NULL);
		exit (128);
	}
	return (0);
}

static void	run_execve(t_minishell *data)
{
	if (execve(data->exec->exec_path, \
	data->exec->cmd_flags, data->env_argv) < 0)
	{
		reset_stdin_stdout(data);
		free(data->exec->exec_path);
		data->exec->exec_path = NULL;
		exit(CMD_NOT_FOUND);
	}
}

void	exec_bash_cmd(t_minishell *data)
{
	if (data->exec->exec_path == NULL \
		&& data->exec->is_builtin == false \
		&& data->exec->is_executable == false)
	{
		my_strerror(data->exec->cmd_flags[0], CMD_NOT_FOUND);
		free(data->exec->exec_path);
		data->exec->exec_path = NULL;
		g_glob_var_exit = CMD_NOT_FOUND;
		exit (CMD_NOT_FOUND);
	}
	if (data->ex_error == true)
	{
		reset_stdin_stdout(data);
		exit(CMD_NOT_FOUND);
	}
	else
		run_execve(data);
	free(data->exec->exec_path);
	data->exec->exec_path = NULL;
	exit(EXIT_SUCCESS);
}
