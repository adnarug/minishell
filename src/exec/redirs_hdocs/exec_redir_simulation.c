/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:02:58 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 16:20:05 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 0
#include "../../../include/minishell.h"

/*Openning the given < redir and swapping it with STDIN*/
static int	change_read(t_prs_tok *token, t_header_prs_tok *prs_lst)
{
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_in = open(token->word, O_RDWR, 0644);
	if (prs_lst->fd_in < 0)
		return (EXIT_FAILURE); // TODO: exit code, signal>
	if (dup2(prs_lst->fd_in, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	if (DEBUG == 1)
		printf("surives read dup2\n");
	if (close(prs_lst->fd_in) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	return (EXIT_SUCCESS);
}

/*Openning the given > redir and swapping it with STDOUT*/
static int	change_write(t_prs_tok *token, t_header_prs_tok *prs_lst)
{
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_out = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (prs_lst->fd_out < 0)
		return (EXIT_FAILURE); // TODO: exit code, signal>
	if (dup2(prs_lst->fd_out, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	if (DEBUG == 1)
		printf("surives write dup2\n");
	if (close(prs_lst->fd_out) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	return (EXIT_SUCCESS);
}

static int	append(t_prs_tok *token, t_header_prs_tok *prs_lst)
{
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_out = open(token->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (prs_lst->fd_out < 0)
		return (EXIT_FAILURE); // TODO: exit code, signal>
	if (dup2(prs_lst->fd_out, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	if (DEBUG == 1)
		printf("surives write dup2\n");
	if (close(prs_lst->fd_out) == -1)
		return (EXIT_FAILURE);// TODO: exit code, signal>
	return (EXIT_SUCCESS);
}

/*Going through all < and > and changing the STDIN and STDOUT accordingly*/
int	resolve_redir(t_prs_tok *prs_token, t_header_prs_tok *prs_lst)
{
	t_prs_tok *tmp_tok;
	int i;

	tmp_tok = prs_token;
	i = 0;
	if (DEBUG == 1)
		printf("****Comes to redir and type is:%s\n", tmp_tok->next->next->word);
	while (tmp_tok != NULL)
	{
		if (tmp_tok->type == '<')
		{
			if (DEBUG == 1)
				printf("**comes to read change, type:%c, word:%s\n", tmp_tok->type, tmp_tok->word);
			change_read(tmp_tok, prs_lst);
		}
		if (tmp_tok->type == '>')
		{
			if (DEBUG == 1)
				printf("**comes to write change, type:%c, word:%s\n", tmp_tok->type, tmp_tok->word);
			change_write(tmp_tok, prs_lst);
		}
		if (tmp_tok->type == '+')
		{
			if (DEBUG == 1)
				printf("**comes to append change, type:%c, word:%s\n", tmp_tok->type, tmp_tok->word);
			append(tmp_tok, prs_lst);
		}
		if (DEBUG == 1)
				printf("**iterations %i\n", i++);
		tmp_tok = tmp_tok->next;
	}
	if (DEBUG == 1)
		printf("**comes out\n");
	return (EXIT_SUCCESS);
}
