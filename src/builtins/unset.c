/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:12:12 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:55:15 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Unseting the env variable, execpt the last on*/

static int	check_node(t_env *node_to_offset)
{
	if (node_to_offset->key == NULL || \
		ft_strncmp(node_to_offset->key, "_", \
			ft_strlen(node_to_offset->key)) == 0)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_minishell *data, t_env *env, char **argv)
{
	int		i;
	int		len;
	t_env	*target_node;

	i = 0;
	len = count_strings(argv);
	if (argv == NULL || len == 0)
		return (EXIT_FAILURE);
	i++;
	while (i < len)
	{
		target_node = ft_lst_find(env, argv[i]);
		if (target_node == NULL)
		{
			strerr_unset("unset", argv[i]);
			g_glob_var_exit = 1;
			i++;
			continue ;
		}
		if (check_node(target_node) == EXIT_SUCCESS)
			data->env_lst = ft_lstdelone_env(target_node, env);
		i++;
	}
	return (g_glob_var_exit);
}
