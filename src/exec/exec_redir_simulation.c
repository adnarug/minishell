/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:02:58 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/24 11:15:16 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	resolve_redir(t_prs_tok *token, t_minishell *data)
{
	t_prs_tok *tmp_tok;

	tmp_tok = token;
	
	while (tmp_tok != NULL)
	{
		if (tmp_tok->type == '<')
			change_read
		if (tmp_tok->type == '>')
			change_write
		tmp_tok = tmp_tok->next;
	}
}

/*Openning the given < redir and swapping it with STDIN*/
int	change_read(t_prs_tok *token, t_minishell *read)
{
	token->fd_in = open(token->word, O_RDWR, 0644);
	if (token->fd_ind < 0)
		return (EXIT_FAILURE); // TODO: exit code, signal>
	dup2(token->fd_in, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}


int	change_write(t_prs_tok *token, t_minishell *read)
{
	token->fd_out = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
}