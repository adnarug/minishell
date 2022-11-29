/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:46:17 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/29 13:13:14 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// static int is_heredoc(t_prs_tok *prs_tok, t_minishell *data)
// {
// 	t_prs_tok	*tmp;
// 	int			num_hdoc;

// 	printf("tmp->type %c\n", tmp->type);
// 	tmp = data->lst_prs->prs_tok;
// 	num_hdoc = 0;
// 	if (tmp->type == HEREDOC)
// 			data->hdoc->num_hdocs++;
// 	printf("hdoc num %d\n", data->hdoc->num_hdocs);
// 	return (num_hdoc);
// }

/*Destroys the temp files created by hdocs
IMPORTANT: path to the file i.e. its name
is matching the index of the hdoc*/
void	destroy_hdocs(t_minishell *data)
{
	int	i;
	char	*path_to_hdoc;

	i = 0;
	if (data->hdoc->fd_tmp == NULL)
		return ;
	while (data->hdoc->fd_tmp[i])
	{
		close(data->hdoc->fd_tmp[i]);
		i++;
	}
	path_to_hdoc = ft_itoa(data->hdoc->index);
	i = 0;
	unlink(path_to_hdoc);
	free(path_to_hdoc);
}

int	count_hdocs(t_minishell *data)
{
	int				counter;
	t_prs_tok		*tmp_prs_tk;
	
	counter = 0;
	while(data->array_sublist[counter] != NULL)
	{
		tmp_prs_tk = data->array_sublist[counter]->prs_tok;
		tmp_prs_tk= data->array_sublist[counter]->prs_tok;
		while(tmp_prs_tk!= NULL)
		{
			if (tmp_prs_tk->type == HEREDOC)
				data->hdoc->num_hdocs++;
			tmp_prs_tk = tmp_prs_tk->next;
		}
		counter++;
	}
	return (EXIT_SUCCESS);
}
