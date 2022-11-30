/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:46:17 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/30 19:02:41 by pguranda         ###   ########.fr       */
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
	int		i;
	char	*path_to_hdoc;

	i = 0;
	if (data->hdoc->fd_tmp == NULL)
		return ;
	while (data->hdoc->fd_tmp[i] && i < data->hdoc->num_hdocs)
	{
		path_to_hdoc = ft_itoa(i);
		if (path_to_hdoc == NULL)
			exit(EXIT_FAILURE) ;
		if (close(data->hdoc->fd_tmp[i]) != 0)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		printf("path to hdoc %s\n", path_to_hdoc);
		if (unlink(path_to_hdoc) != 0)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		free(path_to_hdoc);
		i++;
	}
	// free(data->hdoc);
	// data->hdoc = NULL;
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
