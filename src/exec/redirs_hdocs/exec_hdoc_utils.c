/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:46:17 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 18:52:16 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	close_unlink(t_minishell *data, char *path_to_hdoc, int i)
{
	i = 5;
	(void)data;
	if (unlink(path_to_hdoc) != 0)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
}

/*Destroys the temp files created by hdocs
IMPORTANT: path to the file i.e. its name
is matching the index of the hdoc*/
void	destroy_hdocs(t_minishell *data)
{
	int		i;
	char	*path_to_hdoc;

	i = 0;
	if (data->hdoc->fd_tmp == NULL)
		return ;
	while (i < data->hdoc->num_hdocs && data->hdoc->fd_tmp[i])
	{
		path_to_hdoc = ft_itoa(i);
		if (path_to_hdoc == NULL)
			exit(EXIT_FAILURE);
		close_unlink(data, path_to_hdoc, i);
		free(path_to_hdoc);
		path_to_hdoc = NULL;
		i++;
	}
	free(data->hdoc->fd_tmp);
	data->hdoc->fd_tmp = NULL;
}

int	count_hdocs(t_minishell *data)
{
	int				counter;
	t_prs_tok		*tmp_prs_tk;

	counter = 0;
	while (data->array_sublist[counter] != NULL)
	{
		tmp_prs_tk = data->array_sublist[counter]->prs_tok;
		while (tmp_prs_tk != NULL)
		{
			if (tmp_prs_tk->type == HEREDOC)
				data->hdoc->num_hdocs++;
			tmp_prs_tk = tmp_prs_tk->next;
		}
		counter++;
	}
	return (EXIT_SUCCESS);
}

void	reassign_hdoc_to_redir(t_minishell *data)
{
	int		i;

	i = 0;
	while (i < data->hdoc->num_hdocs)
	{
		free(data->hdoc->hdocs_nodes[i]->word);
		data->hdoc->hdocs_nodes[i]->word = NULL;
		data->hdoc->hdocs_nodes[i]->type = REDIRECT_IN;
		data->hdoc->hdocs_nodes[i]->word = ft_itoa(i);
		i++;
	}
}
