/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:22:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 16:38:18 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 1

#include "../../include/minishell.h"

char **init_builtins_arr(char **builtins)
{
	builtins[0] = "cd";
	builtins[1] = "echo";
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
	char	**cmd_flags;
	char	*token;
	t_env	*env;

	// token = token_node->cmd_flags[0];
	// printf("%s\n", token);
	env = data->env_lst;
	// cmd_flags = ft_split(token, ' ');
	if (ft_strncmp(data->exec->cmd_flags[0], "cd", ft_strlen("cd")) == 0)
		builtin_cd(env, data->exec->cmd_flags);
	
	//ENV
	if (ft_strncmp(data->exec->cmd_flags[0], "env", ft_strlen("env")) == 0)
	{
		builtin_env(env, data->exec->cmd_flags[0]);
		write (2, "check\n",6);
		return (EXIT_SUCCESS);
	}
	// pwd
	// if (ft_strncmp(token, "pwd", ft_strlen("pwd")) == 0)
	// 	builtin_pwd(cmd_flags[0]);
	//UNSET
	if (ft_strncmp(data->exec->cmd_flags[0], "unset", ft_strlen("unset")) == 0)
		builtin_unset(env, data->exec->cmd_flags);
	// EXPORT
	if (ft_strnstr(data->exec->cmd_flags[0], "export", ft_strlen("export ")) != NULL)
	{
		// token += ft_strlen("export ");
		builtin_export(env, data->exec->cmd_flags);
	}
	//EXIT
	// exit_args = ft_split(token, ' ');
	if (ft_strnstr(token, "exit", ft_strlen("exit")) != NULL)
		builtin_exit(data->exec->cmd_flags);

	return (EXIT_SUCCESS);
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

// t_prs_tok *iter_until_cmd(t_header_prs_tok *header)
// {
// 	while (header != NULL)
// 	{
// 		while(header->prs_tok != NULL)
// 		{
// 			if (header->prs_tok->type == COMMAND)
// 			{
// 				if (DEBUG == 1)
// 					printf("returns the comand\n");
// 				return (header->prs_tok);
// 			}
// 			header->prs_tok = header->prs_tok->next;
// 		}
// 		header = header->next;
// 	}
// 	return (NULL);
// }


/***********************************************************/


/* Redirects the last non-builtin command. */

// void	ft_signals(int flag)
// {
// 	if (flag == MAIN_PROCESS)
// 	{
// 		signal(SIGINT, &ctrl_c);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	else if (flag == CHILD_PROCESS)
// 	{
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGINT, &catch_ctrlc);
// 	}
// 	else if (flag == HDOC)
// 	{
// 		signal(SIGQUIT, SIG_IGN);
// 		signal(SIGINT, &ctrl_c);
// 		signal(SIGINT, (void *)catch_herd);
// 		if (catch_herd(99) == 42)
// 			exit(TERMINATED_BY_CTRL_C);
// 	}
// }

/*
	Extracts the cmd and path and executes the given token (cmd).
	Redirects the cmd input/output based on the cmd number.
*/
void	exec_cmd(t_minishell *data, t_header_prs_tok *token)
{
	// extract_cmd_and_path(data, token); let say we have the cmd and the path to it
	data->exec->cmd_flags = token->prs_tok->cmd_flags;
	if (is_builtin(token->prs_tok) == 0)
		find_correct_paths(token->prs_tok, data);
	else
	{
		printf("builtin detected\n");
		data->exec->is_builtin = true;
	}
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
	// free_cmd_and_path(data);
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
	data->exec->cmd_num = 0;//HARDCODED FOR SIMILATION TODO:reset
	data->exec->last_cmd = 1;
	data->pid = 0;
	data->prs_error = false;
	data->lx_error = false;
	data->ex_error = false;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
}

void	execute_tokens(t_minishell *data)
{
	t_header_prs_tok *tmp_node;

	tmp_node = data->lst_prs;
	init_exec(data);
	dup_stdin_and_stdout(data);
	data->hdoc.index= 0;
	resolve_hdocs(data);
	// while (tmp_node != NULL)
	// {
	// 	reset_params(data);
	// 	// resolve_redirections(data); to be conenected
	// 	if (!tmp_node)
	// 	{
	// 		reset_stdin_stdout(data);
	// 		// set_global_exit_code(data);
	// 	}
	// 	else if (tmp_node->prs_tok->type == COMMAND)//flag for no cmd to be set somewhere
	// 	{
	// 		if (DEBUG == 1)
	// 			printf("command for exec :%s\n", tmp_node->prs_tok->cmd_flags[0]);
	// 		exec_cmd(data, tmp_node);
	// 		data->exec->cmd_num++;
	// 	}
	// 	tmp_node = tmp_node->next;
	// 	close_fds_in_out(data);
	// 	// delete_words(data);
	// 	// ft_del_first_token(&data);
	// }
	// catch_exit_code(data);
	// // destroy_hdocs(data);
	printf("finishes execution\n");
	// system("leaks minishell");
}
