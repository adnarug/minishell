/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:49:23 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/20 13:57:29 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*TODOs: 1. cd src after cd does not work, but just cd src works*/
static int	exit_cd(int exit_status, char *command, char *cwd)
{
	if (cwd != NULL)
	{
		free(cwd);
		cwd = NULL;
	}
	if (exit_status == EXIT_SUCCESS)
		return(EXIT_SUCCESS);
	else
	{
		printf("minishell: cd: %s: %s\n", command, strerror(errno));
		return (EXIT_FAILURE);
	}
}

static int	cd_home(char *argv, t_env *env)//to be adjusted based on the token 
{
	t_env	*target_node;
	t_env	*path_home;

	path_home = ft_lst_find(env, "HOME"); 
	if (path_home == NULL)
		exit_cd(EXIT_FAILURE, argv, NULL);
	target_node = ft_lst_find(env, "OLDPWD");
	target_node->value = ft_lst_find(env, "PWD")->value;
	if (target_node->value == NULL)
		return (EXIT_FAILURE);
	if (chdir(path_home->value) == -1)
		exit_cd(EXIT_FAILURE, argv, NULL);
	target_node = ft_lst_find(env, "PWD");
	target_node->value = path_home -> value;
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_env *env, char **argv)//should be **argv, to be adjusted based on the cd token
{
	char	*current_path;
	t_env	*target_env_node;
	DIR		*directory;
	int		i;

	i = 0;
	current_path = NULL;
	if (argv[1] == NULL)
	{
		cd_home(argv[i], env);
		return (EXIT_SUCCESS);
	}
	directory = opendir(argv[1]);
	if (directory == NULL)
		return(exit_cd(EXIT_FAILURE, argv[1], current_path));
	else if (closedir(directory) != 0)
		return (exit_cd(EXIT_FAILURE, argv[1], NULL));
	if (chdir(argv[1]) != 0)
		return (exit_cd(EXIT_FAILURE, argv[1], NULL));
	target_env_node = ft_lst_find(env, "OLDPWD");
 	target_env_node->value = ft_lst_find(env, "PWD")->value;
	current_path = getcwd(current_path, 0);
	target_env_node = ft_lst_find(env, "PWD");
	target_env_node -> value = current_path;

	return (EXIT_SUCCESS);
}
