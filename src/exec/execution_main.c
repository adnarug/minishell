/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:22:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/08 11:41:41 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execution(t_minishell *data)
{
	// char		*argv[] = {"PATH", "_", NULL}; PATH
	// char		**exit_args; EXIT 

	// CD
	char	**cmd_flags;
	char	*token;
	t_env	*env;
	
	token = data->line;
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
	{
		builtin_exit(cmd_flags);
	}
}