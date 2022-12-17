/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:18:40 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 19:56:31 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*Array for checking if the cmd is a builtin*/
static char	**init_builtins_arr(char **builtins)
{
	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "exit";
	builtins[3] = "unset";
	builtins[4] = "env";
	builtins[5] = "export";
	builtins[6] = "pwd";
	builtins[7] = NULL;
	return (builtins);
}

int	is_builtin(t_prs_tok *token)
{
	char			*builtins[9];
	int				i;

	i = 0;
	init_builtins_arr(builtins);
	while (i < 7)
	{
		if (token->cmd_flags != NULL \
		&& ft_strcmp(token->cmd_flags[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*Executing the right builtin, returning glob var*/
int	exec_builtin(t_minishell *data)
{
	t_env	*env;

	env = data->env_lst;
	if (ft_strncmp(data->exec->cmd_flags[0], "cd", ft_strlen("cd")) == 0)
		g_glob_var_exit = builtin_cd(env, data->exec->cmd_flags);
	if (ft_strncmp(data->exec->cmd_flags[0], "env", ft_strlen("env")) == 0)
		g_glob_var_exit = builtin_env(env, data->exec->cmd_flags[0]);
	if (ft_strncmp(data->exec->cmd_flags[0], "echo", ft_strlen("echo")) == 0)
		g_glob_var_exit = builtin_echo(data);
	if (ft_strncmp(data->exec->cmd_flags[0], "pwd", ft_strlen("pwd")) == 0)
		g_glob_var_exit = builtin_pwd(data->exec->cmd_flags[0]);
	if (ft_strncmp(data->exec->cmd_flags[0], "unset", ft_strlen("unset")) == 0)
		g_glob_var_exit = builtin_unset(data, env, data->exec->cmd_flags);
	if (ft_strncmp(data->exec->cmd_flags[0], \
		"export", ft_strlen("export")) == 0)
		g_glob_var_exit = builtin_export(data);
	if (ft_strncmp(data->exec->cmd_flags[0], "exit", ft_strlen("exit")) == 0)
		g_glob_var_exit = builtin_exit(data);
	return (g_glob_var_exit);
}
