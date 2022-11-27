/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rm_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:57:54 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/27 17:50:49 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_pipe(t_minishell *data)
{
	if (pipe(data->pipe) < 0)
	{
		perror(NULL);
		// free_cmd_and_path(data);
		return (-1);
	}
	return (0);
}

void	redirect_stdin_to_pipe(t_minishell *data)
{
	close(data->pipe[1]);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[0]);
}

int	create_fork(t_minishell *data)
{
	// signal(SIGINT, SIG_IGN);
	data->pid = fork();
	if (data->pid < 0)
	{
		perror(NULL);
		// free_cmd_and_path(data);
		return (-1);
	}
	return (0);
}

void	redirect_transitory_cmd(t_minishell *data)
{
	close(data->pipe[0]);
	if (data->std_in != STDIN_FILENO)
	{
		if (dup2(data->std_in, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->std_in);
	}
	if (data->std_out != STDOUT_FILENO)
	{
		if (dup2(data->std_out, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->std_out);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[1]);
}

void	exec_bash_cmd(t_minishell *data)
{
	if (data->ex_error == true)
	{
		reset_stdin_stdout(data);
		// exec_error(CMD_NOT_FOUND, data->exec->cmd[0]);
		exit(CMD_NOT_FOUND);
	}
	else
	{
		if (execve(data->exec->exec_path, data->exec->cmd_flags, (char * const*)data->env_lst) < 0)
		{
			reset_stdin_stdout(data);
			// exec_error(CMD_NOT_FOUND, data->exec->cmd[0]);
			exit(CMD_NOT_FOUND);
		}
	}
	exit(EXIT_SUCCESS);
}


void	reset_params(t_minishell *data)
{
	data->prs_error = false;
	data->ex_error = false;
	data->exec->no_cmd = false;
	data->lst_prs->fd_in = STDIN_FILENO;
	data->lst_prs->fd_out = STDOUT_FILENO;
}

//To be done somewhere else
void	dup_stdin_and_stdout(t_minishell *data)
{
	data->std_in = dup(STDIN_FILENO);
	if (!data->std_in)
	{
		// free(data->fd);
		exit(EXIT_FAILURE);
	}
	data->std_out = dup(STDOUT_FILENO);
	if (!data->std_out)
	{
		// free(data->fd);
		exit(EXIT_FAILURE);
	}
}

void	reset_stdin_stdout(t_minishell *data)
{
	dup2(data->std_in, STDIN_FILENO);
	dup2(data->std_out, STDOUT_FILENO);
}

void	catch_exit_code(t_minishell *data)
{
	int	status;

	// status = g_exit_code;
	printf("pid %d", data->pid);
	waitpid(data->pid, &status, 0);
	// if (WIFEXITED(status))
	// 	g_exit_code = WEXITSTATUS(status);
}

void	close_fds_in_out(t_minishell *data)
{
	if (data->std_in != STDIN_FILENO)
		close(data->std_in);
	if (data->std_out != STDOUT_FILENO)
		close(data->std_out);
}
