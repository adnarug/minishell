/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:46:17 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 17:09:34 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int is_heredoc(t_prs_tok *prs_tok)
{
	t_prs_tok	*tmp;
	int			num_hdoc;

	tmp = prs_tok;
	num_hdoc = 0;
	while (tmp != NULL)
	{
		printf("type %c word %s \n", tmp->type, tmp->word);
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
	while (data->hdoc.fd_tmp[i])
	{
		close(data->hdoc.fd_tmp[i]);
		i++;
	}
	path_to_hdoc = ft_itoa(data->hdoc.index);
	i = 0;
	unlink(path_to_hdoc);
	free(path_to_hdoc);
}

int	count_hdocs(t_minishell *data)
{
	t_header_prs_tok *tmp_prs_lst;
	int	i;

	tmp_prs_lst = data->lst_prs;
	i = 0;
	while (tmp_prs_lst != NULL)
	{
		// printf("%c\n", tmp_prs_lst->prs_tok->type);
		// data->hdoc.num_hdocs += is_heredoc(data->lst_prs->prs_tok);
		if (tmp_prs_lst->prs_tok->type == HEREDOC)
			data->hdoc.num_hdocs++;
		tmp_prs_lst = tmp_prs_lst->next;
	}
	return (EXIT_SUCCESS);
}
