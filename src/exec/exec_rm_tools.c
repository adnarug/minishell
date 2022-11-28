/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rm_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:57:54 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 14:58:02 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define DEBUG 1
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
	data->exec->is_builtin = false;
	data->exec->no_cmd = false;
	data->curr_fd_in = STDIN_FILENO;
	data->curr_fd_out = STDOUT_FILENO;
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

	waitpid(data->pid, &status, 0);
	// if (WIFEXITED(status))
	// 	g_exit_code = WEXITSTATUS(status);
}

void	close_fds_in_out(t_minishell *data)
{
	if (data->curr_fd_in != STDIN_FILENO)
		close(data->curr_fd_in);
	if (data->curr_fd_out != STDOUT_FILENO)
		close(data->curr_fd_out);
}


// void	pipe_transitory_cmd(t_minishell *data)
// {
// 	int	builtin;

// 	if (create_pipe(data) < 0)
// 		return ;
// 	// if (data->exec->no_cmd == true || data->parse_error == true)
// 	// {
// 	// 	redirect_stdin_to_pipe(data);
// 	// 	return ;
// 	// }
// 	if (data->exec->is_builtin == true && data->exec->last_cmd > 1)
// 		exec_transitory_builtin(data);
// 	else
// 	{
// 		if (create_fork(data) < 0)
// 			return ;
// 		if (data->pid == 0)
// 		{
// 			// ft_signals(CHILD_PROCESS);
// 			redirect_transitory_cmd(data);
// 			exec_bash_cmd(data);
// 		}
// 		redirect_stdin_to_pipe(data);
// 	}
// }