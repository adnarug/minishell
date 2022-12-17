/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:50:12 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 14:00:33 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	once we find < or >, it will check next char if 
	we have  <<, >>. We will save the info into the token
*/
void	lex_redirect(t_minishell *data, t_lexing *lex_struct)
{
	int	redir_repeted;

	redir_repeted = 0;
	if (data->line[lex_struct->c_pos] == data->line[lex_struct->c_pos + 1])
		redir_repeted = 1;
	if (data->line[lex_struct->c_pos] == REDIRECT_IN)
	{
		lex_struct->type = REDIRECT_IN;
		if (redir_repeted)
			lex_struct->type = HEREDOC;
	}
	else
	{		
		lex_struct->type = REDIRECT_OUT;
		if (redir_repeted)
			lex_struct->type = APPEND;
	}
	lex_struct->c_pos = lex_struct->c_pos + 1 + redir_repeted;
}

/*
	Tokenices  the metacharacters.
	We are in one of the metacharacters. If it is < or >,
	it will check if it is repeated (<<, >>).
	Otherwise, it will be a pipe.
	We will also keep the number of pipes found.
*/
void	lexer_meta(t_minishell *data, t_lexing *lex_struct)
{
	t_nod_token	*new_token;

	if (ft_isredirect(data->line[lex_struct->c_pos]))
		lex_redirect(data, lex_struct);
	else
	{
		lex_struct->type = PIPE;
		lex_struct->c_pos += 1;
		data->number_pipes += 1;
	}
	lex_struct->buff = ft_strdup("Metachar");
	new_token = create_tok(lex_struct);
	add_toke_list(&(data->list), new_token);
	lex_struct->buff = NULL;
}
