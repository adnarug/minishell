/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:12:12 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/28 11:03:37 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Unseting the env variable, but removing the node t_env*/

static int	check_node(t_env *node_to_offset)
{
	if (node_to_offset->key == NULL || ft_strncmp(node_to_offset->key, "_", ft_strlen(node_to_offset->key)) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_env *env, char **argv)//working with string, to be implemented with a 2d array
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
			i++;
			continue ;
		}
		fflush(stdout);
		if (check_node(target_node) == EXIT_SUCCESS)
			ft_lstdelone_env(target_node, env);
		i++;
	}
	return (EXIT_SUCCESS);
}