/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:49:23 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 20:15:10 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exit_cd(int exit_status, char *command, char *cwd, \
			bool unset_home_flag)
{
	if (cwd != NULL)
	{
		free(cwd);
		cwd = NULL;
	}
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		if (unset_home_flag == true)
			ft_putstr_fd("minishell : cd: HOME is unset\n", 2);
		else
			printf("minishell: cd: %s: %s\n", command, strerror(errno));
		g_glob_var_exit = 1;
		return (EXIT_FAILURE);
	}
}

static int	cd_home(char *argv, t_env *env)
{
	t_env	*target_node;
	t_env	*path_home;

	path_home = ft_lst_find(env, "HOME");
	target_node = ft_lst_find(env, "OLDPWD");
	if (target_node != NULL)
	{
		free(target_node->value);
		target_node->value = NULL;
		target_node->value = ft_strdup(ft_lst_find(env, "PWD")->value);
		if (target_node->value == NULL)
			return (EXIT_FAILURE);
	}
	if (chdir(path_home->value) == -1)
		exit_cd(EXIT_FAILURE, argv, NULL, false);
	target_node = ft_lst_find(env, "PWD");
	if (target_node != NULL)
	{
		free(target_node->value);
		target_node->value = NULL;
		target_node->value = ft_strdup(path_home -> value);
		if (target_node->value == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	swap_nodes(t_env *env, char *curr_path)
{
	t_env	*old;
	t_env	*curr;
	char	*new_old;
	char	*new_curr;

	curr = ft_lst_find(env, "PWD");
	if (curr == NULL)
		return (EXIT_FAILURE);
	old = ft_lst_find(env, "OLDPWD");
	if (old == NULL)
		return (EXIT_FAILURE);
	new_old = ft_strdup(curr->value);
	if (new_old == NULL)
		return (EXIT_FAILURE);
	new_curr = ft_strdup(curr_path);
	if (new_curr == NULL)
		return (EXIT_FAILURE);
	free(curr->value);
	curr->value = NULL;
	curr->value = new_curr;
	free(old->value);
	old->value = NULL;
	old->value = new_old;
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_env *env, char **argv)
{
	char	*current_path;
	DIR		*directory;

	current_path = NULL;
	if (ft_lst_find(env, "HOME") == NULL)
		return (exit_cd(EXIT_FAILURE, argv[1], current_path, true));
	if (argv[1] == NULL)
	{
		cd_home(argv[0], env);
		return (EXIT_SUCCESS);
	}
	directory = opendir(argv[1]);
	if (directory == NULL)
		return (exit_cd(EXIT_FAILURE, argv[1], current_path, false));
	else if (closedir(directory) != 0)
		return (exit_cd(EXIT_FAILURE, argv[1], NULL, false));
	if (chdir(argv[1]) != 0)
		return (exit_cd(EXIT_FAILURE, argv[1], NULL, false));
	current_path = getcwd(current_path, MAXPATHLEN);
	if (swap_nodes(env, current_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free(current_path);
	current_path = NULL;
	return (EXIT_SUCCESS);
}
