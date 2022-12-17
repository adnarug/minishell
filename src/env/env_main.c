/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:47:08 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 11:38:14 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	default_env(char **envp)
{
	int		i;
	char	*curr_path;

	i = 0;
	curr_path = NULL;
	curr_path = getcwd(curr_path, 0);
	envp[0] = ft_strjoin("PWD=", curr_path);
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_strdup("_=/usr/bin/env");
	free(curr_path);
	curr_path = NULL;
}

void	ft_env(t_minishell *data, char **envp)
{
	char		**dup_env;
	int			flag;

	flag = 0;
	if (getenv("PATH") == NULL)
	{
		flag = 1;
		default_env(envp);
	}
	dup_env = dup_env_matrix(envp);
	data->env_argv = dup_env;
	data->env_lst = create_env_lst(dup_env);
	if (flag == 1)
	{
		free(envp[0]);
		free(envp[1]);
		free(envp[2]);
	}
}
