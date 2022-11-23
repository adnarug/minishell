/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:22:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/23 16:36:24 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Big quesitons:
- How does the overall sequence of the execution works?
- Is the created env sufficient. */

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

// void	ft_execution(t_minishell *data)
// {

// 	// printf("%s\n", data->list.head->name);
// 	if (is_builtin(data) == 1)
// 		exec_builtin(tokens_lst, data);
// 	else
// 		cmd_exec(tokens_lst, data)
// }

 int	exec_builtin(t_prs_tok *token_node, t_minishell *data)
{
	char	**cmd_flags;
	char	*token;
	t_env	*env;
	
	token = token_node->cmd_flags[0];
	printf("%s\n", token);
	env = data->env_lst;
	cmd_flags = ft_split(token, ' ');
	if (ft_strncmp(token, "cd", ft_strlen("cd")) == 0)
		builtin_cd(env, cmd_flags);
	
	//ENV
	if (ft_strncmp(token, "env", ft_strlen("env")) == 0)
		builtin_env(env, token);

	// pwd
	// if (ft_strncmp(token, "pwd", ft_strlen("pwd")) == 0)
	// 	builtin_pwd(cmd_flags[0]);
	
	//UNSET
	if (ft_strncmp(token, "unset", ft_strlen("unset")) == 0)
		builtin_unset(env, cmd_flags);
	
	// // EXPORT
	// if (ft_strnstr(token, "export", ft_strlen("export ")) != NULL)
	// {
	// 	// token += ft_strlen("export ");
	// 	builtin_export(env, cmd_flags);
	// }

	//EXIT
	// exit_args = ft_split(token, ' ');
	if (ft_strnstr(token, "exit", ft_strlen("exit")) != NULL)
		builtin_exit(cmd_flags);

	return (EXIT_SUCCESS);
}

int run_execution(t_prs_tok *token, t_minishell *data)
{
	//taking the tokes of the input and the output file from the struct
	//running the execution 
	printf("FD IN:%d\n", token->fd_in);
	printf("FD OUT: %d\n", token->fd_out);
	dup2(token->fd_in, STDIN_FILENO);
	dup2(token->fd_out, STDOUT_FILENO);
	printf("***toke->exec_pat:%s", token->exec_path);
	printf("comes to exec\n");
	if (execve(token->exec_path, token->cmd_flags, (char*const *)data->env_lst) == -1)
		perror("Error\nExecve issue in the child");
	return (EXIT_SUCCESS);
}

int	cmd_exec(t_prs_tok *token, t_minishell *data)
{
	pid_t	pid;
	int		state;

	token->fd_in = open("in_file", O_RDWR, 0777);
	token->fd_out = open("out_file", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (find_correct_paths(token, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (token->exec_path == NULL)
		printf("minishell: command not found\n"); // not correct message
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		return (run_execution(token, data));
	}
 
	close(token->fd_in);
	close(token->fd_out);
	waitpid(pid, &state, 0);
	return (EXIT_SUCCESS);
}

//Convering a token from a list to argv for execution
static char	**token_lst_to_argv(t_nod_token *token)
{
	char		**argv;
	t_nod_token	*tmp_head;
	t_nod_token	*tmp2_head;
	int			i;
	int			counter;

	i = 0;
	counter = 0;
	tmp_head = token;
	tmp2_head = token;
	argv = NULL;
	printf("%s\n", tmp_head->name);
	while (tmp_head != NULL)
	{
		if (ft_strcmp(tmp_head->name, "Meta") != 0)
		{
			i++;
			tmp_head = tmp_head->next;
		}
		else
			break;
	}
	argv = malloc (sizeof(char *) * (i + 1));
	if (argv == NULL)
		return (NULL);
	while (tmp2_head != NULL && counter < i)
	{
		if (tmp2_head->name == NULL)
			break ;
		argv[counter] = tmp2_head->name;
		counter++;
		tmp2_head = tmp2_head->next;
	}
	argv[counter] = NULL;
	return (argv);
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


t_prs_tok *iter_until_cmd(t_header_prs_tok *header)
{
	while (header != NULL)
	{
		while(header->tokens != NULL)
		{
			if (header->tokens->type == 'c')
				return (header->tokens);
			header->tokens = header->tokens->next;
		}
		header = header->next;
	}
	return (NULL);
}

int	ft_execution(t_minishell *data)
{
	t_prs_tok	*token;
	
	token = iter_until_cmd(data->header);
	if (token == NULL)
		return (EXIT_FAILURE);
	printf("%s", token->cmd_flags[0]);
	if (is_builtin(token) == 1)
		exec_builtin(token, data);
	else
	{
		// tokens_lst->argv = token_lst_to_argv(token);
		// counter = count_strings(tokens_lst->argv);
		cmd_exec(token, data);
	}
	return (EXIT_SUCCESS);
}