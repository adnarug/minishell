/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:46:17 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/25 15:50:45 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_heredoc(t_prs_tok *prs_tok)
{
	t_prs_tok	*tmp;
	int			num_hdoc;

	tmp = prs_tok;
	num_hdoc = 0;
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC)
			num_hdoc++;
		tmp = tmp->next;
	}
	return (num_hdoc);
}

/*Destroys the temp files created by hdocs
IMPORTANT: path to the file i.e. its name
is matching the index of the hdoc*/
void	destroy_hdocs(t_minishell *data)
{
	int	i;
	char	*path_to_hdoc;

	if (data->hdoc.fd_tmp == NULL)
		return ;
	path_to_hdoc = ft_itoa(data->hdoc.index);
	i = 0;
	unlink(path_to_hdoc);
	free(path_to_hdoc);
}

int	count_hdocs(t_minishell *data)
{
	t_header_prs_tok *tmp_prs_lst;

	tmp_prs_lst = data->lst_prs;
	while (tmp_prs_lst != NULL)
	{
		if (is_heredoc(data->lst_prs->prs_tok) != 0)
			data->hdoc.num_hdocs += is_heredoc(data->lst_prs->prs_tok);
		tmp_prs_lst = tmp_prs_lst->next;
	}
	return (EXIT_SUCCESS);
}
