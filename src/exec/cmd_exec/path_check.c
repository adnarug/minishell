/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 08:18:02 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/10 14:06:10 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	**add_path_sign(char **path_to_builtins, t_minishell *data)
{
	char	**builtin_paths_final;
	int		line_count;
	int		i;

	i = 0;
	line_count = count_strings(path_to_builtins);
	builtin_paths_final = malloc(sizeof(char *) * (line_count + 1));
	if (builtin_paths_final == NULL)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	while (path_to_builtins[i] != NULL)
	{
		builtin_paths_final[i] = ft_strjoin(path_to_builtins[i], "/");
		i++;
	}
	builtin_paths_final[i] = NULL;
	ft_free_2d(path_to_builtins);
	return (builtin_paths_final);
}

char	*check_paths(char **path_to_builtins, char *command)
{
	char	*string_to_check;
	char	*correct_string;
	int		i;

	i = 0;
	while (path_to_builtins[i] != NULL)
	{
		string_to_check = ft_strjoin(path_to_builtins[i], command);
		if (string_to_check == NULL)
			return (NULL);
		if (access(string_to_check, F_OK) == 0)
		{
			correct_string = ft_strdup(string_to_check);
			free(string_to_check);
			string_to_check = NULL;
			return (correct_string);
		}
		else
		{
			free(string_to_check);
			string_to_check = NULL;
			i++;
		}
	}
	return (NULL);
}

char	**find_path(char **envp)
{
	char	*path;
	int		i;
	char	**path_to_builtins;

	path = NULL;
	i = 0;
	if (envp == NULL || *envp == NULL)
		return (NULL);
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = envp[i];
	path_to_builtins = ft_split(path + 5, ':');
	return (path_to_builtins);
}

int	find_correct_paths(t_prs_tok *parameters, t_minishell *data)
{
	char	**path_to_builtins;
	t_env	*path_var;

	path_to_builtins = NULL;
	path_var = ft_lst_find(data->env_lst, "PATH");
	if (path_var == NULL)
		return (EXIT_FAILURE);
	path_to_builtins = ft_split(path_var->value, ':');
	if (path_to_builtins == NULL)
	{
		my_strerror("command is not found\n", 127);
		exit (127);
	}
	if (path_to_builtins == NULL)
		printf("Error\nCould not find the PATH =");
	path_to_builtins = add_path_sign(path_to_builtins, data);
	data->exec->exec_path = \
		check_paths(path_to_builtins, parameters->cmd_flags[0]);
	ft_free_2d(path_to_builtins);
	if (data->exec->exec_path == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
