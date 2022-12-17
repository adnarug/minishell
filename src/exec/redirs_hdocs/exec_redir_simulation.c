/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:02:58 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:00:00 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*Openning the given < redir and swapping it with STDIN*/
static int	change_read(t_prs_tok *token, t_sublist_prs_tok *prs_lst, \
	t_minishell *data)
{
	(void)data;
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_in = open(token->word, O_RDONLY, 0644);
	if (prs_lst->fd_in < 0)
	{
		if (access(token->word, F_OK) != 0)
			my_strerror(token->word, NO_FILE_OR_DIR);
		else if (access(token->word, R_OK) != 0)
			cmd_str_access(token->word);
		g_glob_var_exit = 1;
		return (EXIT_FAILURE);
	}
	if (data->curr_fd_in != -1)
		close(data->curr_fd_in);
	data->curr_fd_in = prs_lst->fd_in;
	return (EXIT_SUCCESS);
}

/*Openning the given > redir and swapping it with STDOUT*/
static int	change_write(t_prs_tok *token, t_sublist_prs_tok *prs_lst, \
	t_minishell *data)
{
	(void)data;
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_out = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (prs_lst->fd_out < 0)
	{
		if (access(token->word, F_OK) != 0)
			my_strerror(token->word, NO_FILE_OR_DIR);
		else if (access(token->word, W_OK) != 0)
			cmd_str_access(token->word);
		g_glob_var_exit = 1;
		return (EXIT_FAILURE);
	}
	if (data->curr_fd_out != -1)
		close(data->curr_fd_out);
	data->curr_fd_out = prs_lst->fd_out;
	return (EXIT_SUCCESS);
}

static int	append(t_prs_tok *token, t_sublist_prs_tok *prs_lst, \
	t_minishell *data)
{
	(void)data;
	if (token->word == NULL)
		return (EXIT_FAILURE);
	prs_lst->fd_out = open(token->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (prs_lst->fd_out < 0)
	{
		if (access(token->word, F_OK) != 0)
			my_strerror(token->word, NO_FILE_OR_DIR);
		else if (access(token->word, W_OK) != 0)
			cmd_str_access(token->word);
		g_glob_var_exit = 1;
		return (EXIT_FAILURE);
	}
	if (data->curr_fd_out != -1)
		close(data->curr_fd_out);
	data->curr_fd_out = prs_lst->fd_out;
	return (EXIT_SUCCESS);
}

/*Going through all < and > and changing the STDIN and STDOUT accordingly*/
int	resolve_redir(t_sublist_prs_tok *prs_lst, t_minishell *data)
{
	t_prs_tok	*tmp_tok;
	int			i;
	int			error;

	i = 0;
	data->curr_fd_in = -1;
	data->curr_fd_out = -1;
	tmp_tok = prs_lst->prs_tok;
	while (tmp_tok != NULL)
	{
		if (tmp_tok->type == '<')
			error = change_read(tmp_tok, prs_lst, data);
		if (tmp_tok->type == '>')
			error = change_write(tmp_tok, prs_lst, data);
		if (tmp_tok->type == '+')
			error = append(tmp_tok, prs_lst, data);
		if (error == EXIT_FAILURE)
			return (EXIT_FAILURE);
		tmp_tok = tmp_tok->next;
	}
	if (data->curr_fd_in == -1)
		data->curr_fd_in = STDIN_FILENO;
	if (data->curr_fd_out == -1)
		data->curr_fd_out = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}
