/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:00:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/24 17:21:56 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 1
#include "../../include/minishell.h"
/*
- Count hdocs
- Malloc fds for hdoc
- Parse hdocs
    - Create hodc files
    - Add path and index
    - Create files and the access
    - Read to hdoc in a child process
        - Read from stdin */

int is_heredoc(t_prs_tok *prs_tok)
{
	t_prs_tok	*tmp;
	int			num_hdoc;

	tmp = prs_tok;
	num_hdoc = 0;
	while (tmp != NULL)
	{
		if (tmp->type == '-')
			num_hdoc++;
		tmp = tmp->next;
	}
	return (num_hdoc);
}

static int	count_hdcos(t_header_prs_tok *prs_lst)
{
	t_header_prs_tok *tmp_prs_lst;

	tmp_prs_lst = prs_lst;
	while (tmp_prs_lst != NULL)
	{
		if (DEBUG == 1)
			printf("tmp_prs_lst->prs_tok->type:%c\n", tmp_prs_lst->prs_tok->type);
		if (is_heredoc(prs_lst->prs_tok) != 0)
			prs_lst->num_hdocs += is_heredoc(prs_lst->prs_tok);
		tmp_prs_lst = tmp_prs_lst->next;
	}
	return (EXIT_SUCCESS);
}

char **create_hdoc_files(t_header_prs_tok *prs_lst)
{
	char	**hdoc_files_table;
	char	*tmp;
	char	*path;
	int		i;
	char	*hdoc_index;
	
	i = 0;
	tmp = ft_strdup("/tmp/");
	hdoc_files_table = malloc(sizeof(char *) * (prs_lst->num_hdocs + 1));
	if (hdoc_files_table == NULL)
		return(EXIT_FAILURE);
	while (i < prs_lst->num_hdocs)
	{
		hdoc_index = ft_itoa(i);
		path = ft_strjoin(tmp, hdoc_index);
		hdoc_files_table[i] = malloc(sizeof(char) * ft_strlen(path));//maybe +1
		if (hdoc_files_table[i] == NULL)
			return (NULL);
		printf("comes to create\n");
		open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
		// if (data->fd->in < 0 || access(hdoc, F_OK) < 0 || access(hdoc, R_OK) < 0)
		// 	return (NULL);
		perror(NULL);
		hdoc_files_table[i] = path;
		free(path);
		path = NULL;
		free(hdoc_index);
		hdoc_index = NULL;
		i++;
	}
	return (hdoc_files_table);
}

int resolve_hdocs(t_minishell	*data)
{
	char	**hdoc_tmp_files;
	
	hdoc_tmp_files = NULL;
	if (count_hdcos(data->lst_prs) == 0)
		return (EXIT_SUCCESS);
	hdoc_tmp_files = create_hdoc_files(data->lst_prs);
	if (DEBUG == 1)
		printf("num of heredocs %i\n", data->lst_prs->num_hdocs);
	free(hdoc_tmp_files);
	return (EXIT_SUCCESS);
}