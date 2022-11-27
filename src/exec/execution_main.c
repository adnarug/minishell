/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:22:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/27 18:05:07 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define DEBUG 1

#include "../../include/minishell.h"

// /*
// Big quesitons:
// - How does the overall sequence of the execution works?
// - Is the created env sufficient. */

// char **init_builtins_arr(char **builtins)
// {
// 	builtins[0] = "cd";
// 	builtins[1] = "echo";
// 	builtins[2] = "exit";
// 	builtins[3] = "unset";
// 	builtins[4] = "env";
// 	builtins[5] = "export";
// 	builtins[6] = "pwd";
// 	builtins[7] = NULL;;
// 	return (builtins);
// }

// // void	ft_execution(t_minishell *data)
// // {

// // 	// printf("%s\n", data->list.head->name);
// // 	if (is_builtin(data) == 1)
// // 		exec_builtin(tokens_lst, data);
// // 	else
// // 		cmd_exec(tokens_lst, data)
// // }

// int	exec_builtin(t_prs_tok *token_node, t_minishell *data)
// {
// 	char	**cmd_flags;
// 	char	*token;
// 	t_env	*env;
	
// 	token = token_node->cmd_flags[0];
// 	printf("%s\n", token);
// 	env = data->env_lst;
// 	cmd_flags = ft_split(token, ' ');
// 	if (ft_strncmp(token, "cd", ft_strlen("cd")) == 0)
// 		builtin_cd(env, cmd_flags);
	
// 	//ENV
// 	if (ft_strncmp(token, "env", ft_strlen("env")) == 0)
// 		builtin_env(env, token);

// 	// pwd
// 	// if (ft_strncmp(token, "pwd", ft_strlen("pwd")) == 0)
// 	// 	builtin_pwd(cmd_flags[0]);
	
// 	//UNSET
// 	if (ft_strncmp(token, "unset", ft_strlen("unset")) == 0)
// 		builtin_unset(env, cmd_flags);
	
// 	// // EXPORT
// 	// if (ft_strnstr(token, "export", ft_strlen("export ")) != NULL)
// 	// {
// 	// 	// token += ft_strlen("export ");
// 	// 	builtin_export(env, cmd_flags);
// 	// }

// 	//EXIT
// 	// exit_args = ft_split(token, ' ');
// 	if (ft_strnstr(token, "exit", ft_strlen("exit")) != NULL)
// 		builtin_exit(cmd_flags);

// 	return (EXIT_SUCCESS);
// }

// int run_execution(t_prs_tok *token, t_minishell *data)
// {
// 	//taking the tokes of the input and the output file from the struct
// 	//running the execution 
// 	// printf("FD IN:%d\n", token->fd_in);
// 	// printf("FD OUT: %d\n", token->fd_out);
// 	// dup2(token->fd_in, STDIN_FILENO);
// 	// dup2(token->fd_out, STDOUT_FILENO);
// 	if (DEBUG == 1)
// 		printf("***token->exec_path:%s", token->exec_path);
// 	if (execve(token->exec_path, token->cmd_flags, (char*const *)data->env_lst) == -1)
// 		perror("Error\nExecve issue in the child");
// 	return (EXIT_SUCCESS);
// }

// int	cmd_exec(t_prs_tok *token, t_minishell *data)
// {
// 	pid_t	pid;

// 	// resolve_hdocs(data);
// 	// if (DEBUG == 1)
// 	// 	printf("heredocs are resolved\n");
// 	// if (DEBUG == 1)
// 	// 	printf("command being executed %c %c\n", token->type,  token->next->next->type);
// 	// resolve_redir(data->lst_prs->prs_tok, data->lst_prs);
// 	token = iter_until_cmd(data->lst_prs);
// 	if (find_correct_paths(token, data) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (token->exec_path == NULL)
// 	// 	printf("minishell: command not found\n"); // not correct message
// 	pid = fork();
// 	if (pid < 0)
// 		return (EXIT_FAILURE);
// 	if (pid == 0)
// 	{
// 		return (run_execution(token, data));
// 	}
// 	wait(NULL);
// 	return (EXIT_SUCCESS);
// }

// //Convering a token from a list to argv for execution
// static char	**token_lst_to_argv(t_nod_token *token)
// {
// 	char		**argv;
// 	t_nod_token	*tmp_head;
// 	t_nod_token	*tmp2_head;
// 	int			i;
// 	int			counter;

// 	i = 0;
// 	counter = 0;
// 	tmp_head = token;
// 	tmp2_head = token;
// 	argv = NULL;
// 	printf("%s\n", tmp_head->name);
// 	while (tmp_head != NULL)
// 	{
// 		if (ft_strcmp(tmp_head->name, "Meta") != 0)
// 		{
// 			i++;
// 			tmp_head = tmp_head->next;
// 		}
// 		else
// 			break;
// 	}
// 	argv = malloc (sizeof(char *) * (i + 1));
// 	if (argv == NULL)
// 		return (NULL);
// 	while (tmp2_head != NULL && counter < i)
// 	{
// 		if (tmp2_head->name == NULL)
// 			break ;
// 		argv[counter] = tmp2_head->name;
// 		counter++;
// 		tmp2_head = tmp2_head->next;
// 	}
// 	argv[counter] = NULL;
// 	return (argv);
// }

// static int	is_builtin(t_prs_tok *token)
// {
// 	char			*builtins[9];
// 	int				i;

// 	i = 0;
// 	init_builtins_arr(builtins);
	
// 	while (i < 7)
// 	{
// 		if (ft_strcmp(token->cmd_flags[0], builtins[i]) == 0)
// 			return (1);
// 		i++;
// 	}
// 	return(0);
// }

t_prs_tok *iter_until_cmd(t_header_prs_tok *header)
{
	while (header != NULL)
	{
		while(header->prs_tok != NULL)
		{
			if (header->prs_tok->type == COMMAND)
			{
				if (DEBUG == 1)
					printf("returns the comand\n");
				return (header->prs_tok);
			}
			header->prs_tok = header->prs_tok->next;
		}
		header = header->next;
	}
	return (NULL);
}

// /*TODO:check for leaking fds*/
// // int	ft_execution(t_minishell *data)
// // {
// // 	t_header_prs_tok	*lst_prs;

// // 	lst_prs = data->lst_prs;
// // 	/*if (previous == NULL)
// // 		routine for none*/
// // 	/*if (current == NULL)
// // 		routine for only one*/
// // 	// t_prs_tok	*token;
	
// // 	// token = iter_until_cmd(data->lst_prs);
// // 	// if (token == NULL)
// // 	// 	return (EXIT_FAILURE);
// // 	// printf("%s", token->cmd_flags[0]);
// // 	// if (is_builtin(token) == 1)
// // 	// 	exec_builtin(token, data);
// // 	// else
// // 	// {
// // 		// tokens_lst->argv = token_lst_to_argv(token);
// // 		// counter = count_strings(tokens_lst->argv);
// // 	while (lst_prs != NULL)//prs_lst to array
// // 	{
// // 		//set stdin  && std_out
// // 		cmd_exec(data->lst_prs->prs_tok, data);
// // 		lst_prs = lst_prs->next;
// // 	}
// // 	// }
// // 	if (DEBUG == 1)
// // 		printf("exiting the ft_execution\n");
// // 	return (EXIT_SUCCESS);
// // }

/***********************************************************/

void	init_exec(t_minishell *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (data->exec == NULL)
		return ;
	data->exec->cmd_flags = NULL;
	data->exec->no_cmd = false;
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

void	pipe_transitory_cmd(t_minishell *data)
{
	int	builtin;

	if (create_pipe(data) < 0)
		return ;
	// if (data->prs_error == true)
	// {
	// 	redirect_stdin_to_pipe(data);
	// 	return ;
	// }
	// builtin = ft_get_builtin(data);
	// if (builtin >= 0)
	// 	exec_transitory_builtin(data, builtin);
	// else
	// {
		if (create_fork(data) < 0)
			return ;
		if (data->pid == 0)
		{
			// ft_signals(CHILD_PROCESS);
			redirect_transitory_cmd(data);
			exec_bash_cmd(data);
		}
		redirect_stdin_to_pipe(data);
	// }
}

/* Redirects the last non-builtin command. */
void	redirect_last_cmd(t_minishell *data)
{
	if (data->std_in != STDIN_FILENO)
	{
		printf("****%d %d***", data->std_in, STDIN_FILENO);
		if (dup2(data->std_in, STDIN_FILENO) < 0)
		{
			printf("error1\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		close(data->std_in);
	}
	if (data->std_out != STDOUT_FILENO)
	{
		if (dup2(data->std_out, STDOUT_FILENO) < 0)
		{
				printf("Error2\n");
			perror (NULL);
			exit (EXIT_FAILURE);
		}
		close(data->std_out);
	}
}

void	ft_signals(int flag)
{
	if (flag == MAIN_PROCESS)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, &catch_ctrlc);
	}
	else if (flag == HDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ctrl_c);
		signal(SIGINT, (void *)catch_herd);
		if (catch_herd(99) == 42)
			exit(TERMINATED_BY_CTRL_C);
	}
}


void	pipe_last_cmd(t_minishell *data)
{
	int	builtin;

	// if (data->exec->no_cmd == true || data->prs_error == true)
	// {
	// 	reset_stdin_stdout(data);
	// 	if (data->prs_error == true)
	// 		// g_exit_code = EXIT_FAILURE;
	// 	return ;
	// }
	// builtin = ft_get_builtin(data);
	// if (builtin >= 0)
	// // 	exec_last_builtin(data, builtin);
	// else
	// {
		if (create_fork(data) < 0)
			return ;
		if (data->pid == 0)
		{
			printf("in the last child \n");
			ft_signals(CHILD_PROCESS);
			printf("fdin: %d fdout: %d pid:%d stdin:%d\n", data->std_in, data->std_out, data->pid, STDIN_FILENO);
			redirect_last_cmd(data);
			exec_bash_cmd(data);
		}
	// }
	reset_stdin_stdout(data);

}

/*
	Extracts the cmd and path and executes the given token (cmd).
	Redirects the cmd input/output based on the cmd number.
*/
void	exec_cmd(t_minishell *data, t_header_prs_tok *token)
{
	// extract_cmd_and_path(data, token); let say we have the cmd and the path to it
	data->exec->cmd_flags = token->prs_tok->cmd_flags;
	find_correct_paths(token->prs_tok, data);
	printf("\ndata->exec_path:%s data->cmd_flags:%s\n", data->exec->exec_path, data->exec->cmd_flags[0] );
	if (data->exec->cmd_num < data->exec->last_cmd)
		pipe_transitory_cmd(data);
	else if (data->exec->cmd_num == data->exec->last_cmd)
	{
		printf("running the last command\n");
		pipe_last_cmd(data);
	}
	// free_cmd_and_path(data);
}

void	execute_tokens(t_minishell *data)
{
	t_header_prs_tok *tmp_node;

	tmp_node = data->lst_prs;
	dup_stdin_and_stdout(data);
	init_exec(data);
	//data->exec->last_cmd = ft_get_num_cmds(data);
	data->hdoc.index= 0;
	while (tmp_node != NULL)
	{
		reset_params(data);
		// resolve_redirections(data); to be conenected
		if (!tmp_node)
		{
			reset_stdin_stdout(data);
			// set_global_exit_code(data);
		}
		else if (tmp_node->prs_tok->type == COMMAND)//flag for no cmd to be set somewhere
		{
			printf("command for exec :%s\n", tmp_node->prs_tok->cmd_flags[0]);
			exec_cmd(data, tmp_node);
			data->exec->cmd_num++;
		}
		close_fds_in_out(data);
		tmp_node = tmp_node->next;
		// delete_words(data);
		// ft_del_first_token(&data);
	}
	catch_exit_code(data);
	// destroy_hdocs(data);
}
