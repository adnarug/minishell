/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:45:04 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 19:20:43 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_or_replace(t_env *node_to_add, char *key, char *val, t_env *list)
{
	if (node_to_add == NULL)
	{
		node_to_add = ft_lstnew_env(key, val);
		ft_lstadd_back_mini(&list, node_to_add);
	}
	else
	{
		free(node_to_add->value);
		node_to_add->value = NULL;
		node_to_add->value = ft_strdup(val);
		free(val);
		val = NULL;
		free(key);
		key = NULL;
	}
}

void	make_envp(char *s, t_minishell *data)
{
	char	*key;
	char	*val;
	int		i;
	t_env	*node_to_add;
	t_env	*list;

	val = NULL;
	list = data->env_lst;
	i = 0;
	key = create_key(s, &i, data);
	if (key == NULL)
	{
		strerr_export("export", INVAL_EXP, s);
		g_glob_var_exit = 1;
		return ;
	}
	val = ft_strchr(s, '=');
	if (val == NULL || *(val++) == '\0')
		val = ft_strdup("");
	else
		val = ft_strdup(val);
	node_to_add = ft_lst_find(list, key);
	add_or_replace(node_to_add, key, val, list);
}

static void	key_export(t_minishell **data)
{
	int	i;
	int	plus;

	plus = 0;
	i = 1;
	while ((*data)->exec->cmd_flags[i])
	{
		if (ft_strchr((*data)->exec->cmd_flags[i], '+') != NULL)
			plus = 1;
		make_envp((*data)->exec->cmd_flags[i], *data);
		i++;
		plus = 0;
	}
}

int	builtin_export(t_minishell *data)
{
	int	return_value;

	return_value = 1;
	if (data->exec->cmd_flags[1] == NULL)
		real_env(data);
	key_export(&data);
	if (return_value != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
