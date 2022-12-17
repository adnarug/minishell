/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:30:53 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 20:08:17 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_lstdelone_env(t_env *node_to_delete, t_env *env)
{
	t_env	*previous_node;

	if (node_to_delete == NULL || env == NULL)
		return (NULL);
	if (env == node_to_delete)
		return (unseting_first_node(node_to_delete, env));
	previous_node = ft_lst_find_previous(env, node_to_delete);
	previous_node->next = node_to_delete->next;
	free(node_to_delete->key);
	node_to_delete->key = NULL;
	free(node_to_delete->value);
	node_to_delete->value = NULL;
	free(node_to_delete);
	node_to_delete = NULL;
	return (env);
}

t_env	*ft_lst_find(t_env *node, char *key)
{
	t_env	*tmp;

	tmp = node;
	if (tmp == NULL || key == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp -> next;
	}
	return (tmp);
}

void	print_env_lst_export(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	print_env_lst(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		if (tmp->value != NULL && ft_strcmp(tmp->value, "") != 0)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	check_for_reset(t_minishell *data, int i)
{
	if (data->array_sublist[i] == NULL)
		reset_stdin_stdout(data);
}
