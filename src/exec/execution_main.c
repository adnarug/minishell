/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:22:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/11 18:10:56 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// void	ft_execution(t_minishell *data)
// {

// 	// printf("%s\n", data->list.head->name);
// 	if (is_builtin(data) == 1)
// 		exec_builtin(tokens_lst, data);
// 	else
// 		cmd_exec(tokens_lst, data)
// }

int	exec_builtin(t_nod_token *token_node, t_minishell *data)
{
	char	**cmd_flags;
	char	*token;
	t_env	*env;
	
	token = token_node->name;
	printf("%s\n", token);
	env = data->env_lst;
	printf("We come here\n");
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

// void	cmd_exec(t_list_token *token, t_minishell *data)
// {
// 	find_correct_paths(tokens, data);
// 	printf("path to exec: %s", token->)
	
// }

int	ft_execution(t_minishell *data)
{
	char			*builtins[9];
	t_nod_token		*tokens_lst;
	int				i;

	i = 0;
	tokens_lst = data->list.head;
	init_builtins_arr(builtins);
	print_2d(builtins);
	while (tokens_lst != NULL && i < 8 && tokens_lst->flag == WORD)
	{
		if (ft_strcmp(tokens_lst->name, builtins[i]) == 0)
		{
			printf("check_mid\n");
			exec_builtin(tokens_lst, data);
			return (1);
		}
		else
		// 	cmd_exec(tokens_lst, data);
			// tokens_lst = tokens_lst->next;
			i++;
		printf("check_end\n");
	}
	return (0);
}