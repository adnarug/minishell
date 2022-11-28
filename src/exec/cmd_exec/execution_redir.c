/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:26:06 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 16:20:43 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
	Executes builtins between pipes (all except the last one).
	Closes unused pipes and redirects the standard input into the next pipe.
*/
void	exec_transitory_builtin(t_minishell *data)
{
	if (data->curr_fd_in != STDIN_FILENO)
	{
		if (dup2(data->curr_fd_in, STDIN_FILENO) < 0)
		{
			printf("error1\n");
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_in);
	}
	if (data->curr_fd_out != STDOUT_FILENO)
	{
		if (dup2(data->curr_fd_out, STDOUT_FILENO) < 0)
		{
			printf("error2\n");
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_out);
	}
	else
	{
		dup2(data->pipe[1], STDOUT_FILENO);
	}
	exec_builtin(data);
	// g_exit_code = data->builtins->funcs[builtin](data);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[1]);
	close(data->pipe[0]);
	dup2(data->std_out, STDOUT_FILENO);
}

/* 
	Executes the last builtin.
	Closes unused pipes and redirects the standard input/output 
	in to the saved std_in and std_out.
*/
void	exec_last_builtin(t_minishell *data)
{
	if (data->curr_fd_in != STDIN_FILENO)
	{
		if (dup2(data->curr_fd_in, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_in);
	}
	if (data->curr_fd_out != STDOUT_FILENO)
	{
		if (dup2(data->curr_fd_out, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_out);
	}
	// g_exit_code = data->builtins->funcs[builtin](data);
	if (exec_builtin(data) == 0)
		printf("Executed last builtin\n");
}

void	redirect_transitory_cmd(t_minishell *data)
{
	close(data->pipe[0]);
	if (data->curr_fd_in != STDIN_FILENO)
	{
		if (dup2(data->curr_fd_in, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_in);
	}
	if (data->curr_fd_out != STDOUT_FILENO)
	{
		if (dup2(data->curr_fd_out, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_out);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[1]);
}

void	redirect_last_cmd(t_minishell *data)
{
	if (data->curr_fd_in != STDIN_FILENO)
	{
		if (dup2(data->curr_fd_in, STDIN_FILENO) < 0)
		{
			printf("error1\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_in);
	}
	if (data->curr_fd_out != STDOUT_FILENO)
	{
		if (dup2(data->curr_fd_out, STDOUT_FILENO) < 0)
		{
			printf("Error2\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		close(data->curr_fd_out);
	}
}

void	redirect_stdin_to_pipe(t_minishell *data)
{
	close(data->pipe[1]);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[0]);
}
