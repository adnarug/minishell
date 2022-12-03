/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:22:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/03 17:03:06 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 0

#include "../../include/minishell.h"

char **init_builtins_arr(char **builtins)
{
	builtins[0] = "cd";
	builtins[1] = "check";
	builtins[2] = "exit";
	builtins[3] = "unset";
	builtins[4] = "env";
	builtins[5] = "export";
	builtins[6] = "pwd";
	builtins[7] = NULL;;
	return (builtins);
}

int	exec_builtin(t_minishell *data)
{
	char	*token;
	t_env	*env;

	// token = token_node->cmd_flags[0];
	// printf("%s\n", token);
	env = data->env_lst;
	// cmd_flags = ft_split(token, ' ');
	if (ft_strncmp(data->exec->cmd_flags[0], "cd", ft_strlen("cd")) == 0)
	{
		builtin_cd(env, data->exec->cmd_flags);
		return (EXIT_SUCCESS);
	}
	//ENV
	if (ft_strncmp(data->exec->cmd_flags[0], "env", ft_strlen("env")) == 0)
	{
		builtin_env(env, data->exec->cmd_flags[0]);
		return (EXIT_SUCCESS);
	}
	//ECHO
	if (ft_strncmp(data->exec->cmd_flags[0], "echo", ft_strlen("echo")) == 0)
	{
		builtin_echo(data->exec->cmd_flags);
		return (EXIT_SUCCESS);
	}
	// PWD
	if (ft_strncmp(data->exec->cmd_flags[0], "pwd", ft_strlen("pwd")) == 0)
	{
		builtin_pwd(data->exec->cmd_flags[0]);
		return (EXIT_SUCCESS);
	}
	//UNSET
	if (ft_strncmp(data->exec->cmd_flags[0], "unset", ft_strlen("unset")) == 0)
	{
		builtin_unset(env, data->exec->cmd_flags);
		return (EXIT_SUCCESS);
	}
	// EXPORT
	if (ft_strnstr(data->exec->cmd_flags[0], "export", ft_strlen("export ")) != NULL)
	{
		// token += ft_strlen("export ");
		builtin_export(env, data->exec->cmd_flags);
		return (EXIT_SUCCESS);
	}
	
	//EXIT
	// exit_args = ft_split(token, ' ');
	if (ft_strnstr(token, "exit", ft_strlen("exit")) != NULL)
	{
		builtin_exit(data->exec->cmd_flags);
		return (EXIT_SUCCESS);
	}

	return (EXIT_FAILURE);
}

static int	is_builtin(t_prs_tok *token)
{
	char			*builtins[9];
	int				i;

	i = 0;
	init_builtins_arr(builtins);
	
	while (i < 7)
	{
		if (ft_strcmp(token->cmd_flags[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return(0);
}

int is_executable(t_minishell *data)
{
	
	if (access(data->exec->cmd_flags[0], F_OK | X_OK) == 0 && ft_strchr(data->exec->cmd_flags[0], '/') != NULL)
	{
		// printf("executable\n");
		// printf("exec: %s", data->exec->cmd_flags[0]);
		// printf("data->execPath %s\n", data->exec->exec_path);
		data->exec->exec_path = data->exec->cmd_flags[0];
		return (1);
	}
		return (0);
}

void	exec_cmd(t_minishell *data, t_sublist_prs_tok *token)
{
	data->exec->cmd_flags = token->prs_tok->cmd_flags;
	if (is_builtin(token->prs_tok) == 0 && is_executable(data) == 0)
		find_correct_paths(token->prs_tok, data);
	else if (is_builtin(token->prs_tok) == 1)
		data->exec->is_builtin = true;
	if (data->exec->exec_path == NULL)
		ft_putstr_fd("bash: : command not found\n", 2);
	if (DEBUG == 1)
		printf("\ndata->exec_path:%s data->cmd_flags:%s\n", data->exec->exec_path, data->exec->cmd_flags[0]);
	if (data->exec->cmd_num < data->exec->last_cmd)
	{
		if (DEBUG == 1)
			printf("running the trans command\n");
		pipe_transitory_cmd(data);
	}
	else if (data->exec->cmd_num == data->exec->last_cmd)
	{
		if (DEBUG == 1)
			printf("running the last command\n");
		pipe_last_cmd(data);
	}
}

void	init_exec(t_minishell *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (data->exec == NULL)
		return ;
	data->exec->cmd_flags = NULL;
	data->curr_fd_in = STDIN_FILENO;
	data->curr_fd_out = STDOUT_FILENO;

	data->exec->no_cmd = false;
	data->exec->is_builtin = false;
	data->exec->exec_path = NULL;
	data->exec->cmd_num = 1;//HARDCODED FOR SIMILATION TODO:reset
	data->exec->last_cmd = data->array_sublist[0]->number_cmd;
	data->pid = 0;
	data->prs_error = false;
	data->lx_error = false;
	data->ex_error = false;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
}

void count_size(t_minishell *data)
{
	int counter;

	counter = 0;
	while (data->array_sublist[counter] != NULL)
		counter++;
	data->array_sublist[0]->number_cmd = counter;
	// if (counter == 0)
	// 	print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
}

int	ft_execution(t_minishell *data)
{
	int		i;

	i = 0;
	count_size(data);
	init_exec(data);
	dup_stdin_and_stdout(data);//need to free t_exec
	data->exec->last_cmd = data->array_sublist[0]->number_cmd;
	resolve_hdocs(data);
	while (data->array_sublist[i] != NULL)
	{
		reset_params(data);
		// printf("%c\n", data->array_sublist[i]->prs_tok->type);
		resolve_redir(data->array_sublist[i], data);
		if (data->array_sublist[i] ==  NULL)
		{
			printf("does it come here|\n");
			reset_stdin_stdout(data);
			// set_global_exit_code(data);
		}
		while (data->array_sublist[i]->prs_tok != NULL)//flag for no cmd to be set somewhere
		{
			if (DEBUG == 1)
				printf("current type:%c\n", data->array_sublist[i]->prs_tok->type);
			if (data->array_sublist[i]->prs_tok->type == COMMAND)
			{
				if (DEBUG == 1)
					printf("enters exec");
				exec_cmd(data, data->array_sublist[i]);
				data->exec->cmd_num++;
				break;
			}
			data->array_sublist[i]->prs_tok = data->array_sublist[i]->prs_tok->next;
		}
		close_fds_in_out(data);
		if (DEBUG == 1)
			printf("exec path :%s", data->exec->exec_path);
		free_cmd_path(data);
		i++;
	}
	// free_cmd_path(data);
	catch_exit_code(data);
	destroy_hdocs(data);	
	if (DEBUG == 1)
		printf("finishes execution\n");
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}


