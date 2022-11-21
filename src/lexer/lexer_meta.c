/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:50:12 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/21 23:54:10 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	once we find < or >, it will check next char if 
	we have  <<, >>. We will save the info into the token
*/
//this functions is creating leaks 
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
	lex_struct->buff = ft_strjoin_char(lex_struct->buff,
			data->line[lex_struct->c_pos]);
	lex_struct->c_pos = lex_struct->c_pos + 1 + redir_repeted;
}

/*
	Tokenices  the metacharacters.
	We are in one of the metacharacters. If it is < or >,
	it will check if it is repeated (<<, >>).
	Otherwise, it will be a pipe.
*/
void	lexer_meta(t_minishell *data, t_lexing *lex_struct)
{
	t_nod_token	*new_token;

	if (ft_isredirect(data->line[lex_struct->c_pos]))
		lex_redirect(data, lex_struct);
	else //find a pipe
	{
		lex_struct->type = PIPE;
		lex_struct->c_pos += 1;
	}
	lex_struct->buff = ft_strdup("Meta"); //ponemos este valor para que creee el nodo
	new_token = create_tok(lex_struct);
	free(lex_struct->buff);
	lex_struct->buff = NULL;
	add_toke_list(&(data->list), new_token);
}