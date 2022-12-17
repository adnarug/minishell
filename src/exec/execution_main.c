/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:22:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:56:50 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Checking if it is relative or absolute path to an executable*/
int	is_executable(t_minishell *data)
{
	if (access(data->exec->cmd_flags[0], F_OK | X_OK) == 0 && \
		ft_strchr(data->exec->cmd_flags[0], '/') != NULL)
	{
		data->exec->exec_path = ft_strdup(data->exec->cmd_flags[0]);
		data->exec->is_executable = true;
		return (1);
	}
	return (0);
}

/*Findning the path for cmd, if it is not a builtin and executing it*/
void	exec_cmd(t_minishell *data, t_prs_tok *token)
{
	data->exec->cmd_flags = token->cmd_flags;
	if (is_builtin(token) == 0 && is_executable(data) == 0)
		find_correct_paths(token, data);
	else if (is_builtin(token) == 1)
		data->exec->is_builtin = true;
	if (data->exec->cmd_num < data->exec->last_cmd)
		pipe_transitory_cmd(data);
	else if (data->exec->cmd_num >= data->exec->last_cmd)
		pipe_last_cmd(data);
	free(data->exec->exec_path);
	data->exec->exec_path = NULL;
}

static void	iter_prs_tok(t_minishell *data, t_prs_tok *tmp)
{
	while (tmp != NULL)
	{
		if (tmp->type == COMMAND)
		{
			exec_cmd(data, tmp);
			data->exec->cmd_num++;
			break ;
		}
		tmp = tmp->next;
	}
}

/*Iterating and executing the cmds with correct redirs*/
static int	execution_iteration(t_minishell *data)
{
	int			i;
	t_prs_tok	*tmp;

	i = 0;
	while (data->array_sublist[i] != NULL)
	{
		reset_params(data);
		if (resolve_redir(data->array_sublist[i], data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		check_for_reset(data, i);
		if (at_least_one_cmd(data, data->array_sublist[i]) == 1)
		{
			tmp = data->array_sublist[i]->prs_tok;
			iter_prs_tok(data, tmp);
			free(data->exec->exec_path);
			data->exec->exec_path = NULL;
			close_fds_in_out(data);
		}
		else
			close_fds_in_out(data);
		i++;
	}
	return (EXIT_SUCCESS);
}

/*Driver execution:
- Resolve hdocs - create files, turn it into '<'
- Going through all cmds to execute*/
int	ft_execution(t_minishell *data)
{
	count_size(data);
	init_exec(data);
	dup_stdin_and_stdout(data);
	data->exec->last_cmd = data->array_sublist[0]->number_cmd;
	resolve_hdocs(data);
	if (data->prs_error == true)
		return (1);
	if (!data->array_sublist)
		return (0);
	if (execution_iteration(data) == EXIT_FAILURE)
	{
		catch_exit_code(data);
		if (data->hdoc->num_hdocs != 0)
			destroy_hdocs(data);
		g_glob_var_exit = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	catch_exit_code(data);
	if (data->hdoc->num_hdocs != 0)
		destroy_hdocs(data);
	return (EXIT_SUCCESS);
}
