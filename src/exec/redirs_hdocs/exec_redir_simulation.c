/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:02:58 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/29 17:15:24 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 0
#include "../../../include/minishell.h"

/*Openning the given < redir and swapping it with STDIN*/
static int	change_read(t_prs_tok *token, t_sublist_prs_tok *prs_lst, t_minishell *data)
{
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_in = open(token->word, O_RDONLY, 0644);
	if (DEBUG == 1)
		printf("prs fd %i\n", prs_lst->fd_in);
	if (prs_lst->fd_in < 0)
		return (EXIT_FAILURE); // TODO: exit code, signal>
	data->curr_fd_in = prs_lst->fd_in;
	// if (dup2(prs_lst->fd_in, data->curr_fd_in) == -1)
	// 	return (EXIT_FAILURE);// TODO: exit code, signal>
	if (DEBUG == 1)
		printf("surives read dup2 with prs fd %i\n", prs_lst->fd_in);
	if (close(prs_lst->fd_in) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	return (EXIT_SUCCESS);
}

/*Openning the given > redir and swapping it with STDOUT*/
static int	change_write(t_prs_tok *token, t_sublist_prs_tok *prs_lst, t_minishell *data)
{
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_out = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (prs_lst->fd_out < 0)
		return (EXIT_FAILURE); // TODO: exit code, signal>
	// if (dup2(prs_lst->fd_out, data->curr_fd_out) == -1)
	// 	return (EXIT_FAILURE);// TODO: exit code, signal>
	data->curr_fd_out = prs_lst->fd_out;
	if (DEBUG == 1)
		printf("surives write dup2\n");
	if (close(prs_lst->fd_out) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	return (EXIT_SUCCESS);
}

static int	append(t_prs_tok *token, t_sublist_prs_tok *prs_lst, t_minishell *data)
{
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_out = open(token->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (prs_lst->fd_out < 0)
		return (EXIT_FAILURE); // TODO: exit code, signal>
	// if (dup2(prs_lst->fd_out, data->curr_fd_out) == -1)
	// 	return (EXIT_FAILURE);// TODO: exit code, signal>
	data->curr_fd_out = prs_lst->fd_out;
	if (DEBUG == 1)
		printf("surives write dup2\n");
	if (close(prs_lst->fd_out) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	return (EXIT_SUCCESS);
}

/*Going through all < and > and changing the STDIN and STDOUT accordingly*/
int	resolve_redir(t_sublist_prs_tok *prs_lst, t_minishell *data)
{
	t_prs_tok *tmp_tok;
	int i;

	tmp_tok = prs_lst->prs_tok;
	i = 0;
	if (DEBUG == 1)
		printf("****Comes to redir and type is:%s\n", tmp_tok->word);
	while (tmp_tok != NULL)
	{
		if (tmp_tok->type == '<')
		{
			if (DEBUG == 1)
				printf("**comes to read change, type:%c, word:%s\n", tmp_tok->type, tmp_tok->word);
			change_read(tmp_tok, prs_lst, data);
		}
		if (tmp_tok->type == '>')
		{
			if (DEBUG == 1)
				printf("**comes to write change, type:%c, word:%s\n", tmp_tok->type, tmp_tok->word);
			change_write(tmp_tok, prs_lst, data);
		}
		if (tmp_tok->type == '+')
		{
			if (DEBUG == 1)
				printf("**comes to append change, type:%c, word:%s\n", tmp_tok->type, tmp_tok->word);
			append(tmp_tok, prs_lst, data);
		}
		if (DEBUG == 1)
				printf("**iterations %i\n", i++);
		tmp_tok = tmp_tok->next;
	}
	if (DEBUG == 1)
		printf("**comes out of redir with curr_fd_in %i curr_fd_out %i STDIN %i STDOUT %o\n", data->curr_fd_in, data->curr_fd_out, STDIN_FILENO, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
