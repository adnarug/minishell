/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:00:15 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 20:11:48 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*unseting_first_node(t_env *node_to_delete, t_env *env)
{
	t_env	*new_head;

	new_head = NULL;
	new_head = node_to_delete->next;
	free(node_to_delete->key);
	node_to_delete->key = NULL;
	free(node_to_delete->value);
	node_to_delete->value = NULL;
	free(node_to_delete);
	node_to_delete = NULL;
	env = new_head;
	return (new_head);
}

void	wait_signal(t_minishell *data, int status)
{
	if (!WIFSIGNALED(status))
	{
		g_glob_var_exit = WEXITSTATUS(status);
		if (g_glob_var_exit == EXIT_FAILURE)
			data->prs_error = true;
	}
	else if (WIFSIGNALED(status))
	{
		g_glob_var_exit = EXIT_FAILURE;
		data->prs_error = true;
	}
}
