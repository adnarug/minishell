/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:00:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/24 16:03:50 by pguranda         ###   ########.fr       */
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

int resolve_hdocs(t_minishell	*data)
{
	count_hdcos(data->lst_prs);
	if (DEBUG == 1)
		printf("num of heredocs %i\n", data->lst_prs->num_hdocs);
	return (EXIT_SUCCESS);
}