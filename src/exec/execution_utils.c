/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:57:55 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:15:19 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_exec(t_minishell *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (data->exec == NULL)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	data->exec->cmd_flags = NULL;
	data->exec->exec_path = NULL;
	data->curr_fd_in = STDIN_FILENO;
	data->curr_fd_out = STDOUT_FILENO;
	data->exec->no_cmd = false;
	data->exec->is_builtin = false;
	data->exec->is_executable = false;
	data->exec->exec_path = NULL;
	data->exec->cmd_num = 1;
	data->pid = 0;
	data->prs_error = false;
	data->lx_error = false;
	data->ex_error = false;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
}

void	init_hdocs(t_minishell *data)
{
	data->hdoc = malloc(sizeof(t_hdocs));
	if (data->hdoc == NULL)
		exec_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	data->hdoc->num_hdocs = 0;
	data->hdoc->index = 0;
	data->hdoc->fd_tmp = NULL;
	data->hdoc->hdocs_nodes = NULL;
	data->hdoc->is_hdoc = false;
}

/*Finds all nodes of t_prs_tok with hdocs, creates
an array of hdocs in data->hdoc*/
t_prs_tok	*find_hdoc_nodes(t_minishell *data)
{
	t_prs_tok		*tmp_prs_tk;
	int				i;
	int				j;
	int				counter;

	i = 0;
	j = 0;
	counter = 0;
	data->hdoc->hdocs_nodes = malloc(sizeof(t_prs_tok *) \
		* (data->hdoc->num_hdocs));
	if (data->hdoc->hdocs_nodes == NULL)
		return (NULL);
	while (data->array_sublist[i] != NULL)
	{
		tmp_prs_tk = data->array_sublist[i]->prs_tok;
		while (tmp_prs_tk != NULL)
		{
			if (tmp_prs_tk->type == HEREDOC)
				data->hdoc->hdocs_nodes[j++] = tmp_prs_tk;
			tmp_prs_tk = tmp_prs_tk->next;
		}
		i++;
	}
	return (NULL);
}

/*Number of pipes in the input*/
void	count_size(t_minishell *data)
{
	int	counter;

	counter = 0;
	while (data->array_sublist[counter] != NULL)
		counter++;
	data->array_sublist[0]->number_cmd = counter;
}

int	at_least_one_cmd(t_minishell *data, t_sublist_prs_tok *list)
{
	bool			cmd_found;
	t_prs_tok		*tmp;

	(void)data;
	tmp = list->prs_tok;
	cmd_found = false;
	while (tmp != NULL)
	{
		if (tmp->type == COMMAND)
		{
			cmd_found = true;
			return (1);
		}
		tmp = tmp->next;
	}
	data->exec->cmd_num++;
	return (0);
}
