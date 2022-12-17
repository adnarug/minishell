/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:56 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 13:55:36 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initializer_lex(t_lexing *lex_struct)
{
	lex_struct->buff = NULL;
	lex_struct->c_pos = 0;
	lex_struct->type = 0;
}

/*
	Declare and initialize the lex_struct structure
	Delete all spaces at the beginning and end of the line.
	Verify that all double/single quotes are correctly closed.
	We go through the line character per character:
	If it finds a space, go to the next char.
	if it finds |, <, >, <<, >>, it tokenizes them and identifies them as such,
	everything else it converts it into a word and identifies it as a word.
*/

void	ft_lexer(t_minishell *data)
{
	t_lexing	lex_struct;

	initializer_lex(&lex_struct);
	data->lx_error = true;
	if (!are_quote_closed(data))
	{
		print_error_free_exit(data, QUOTE_ERR, QUOTE_ERR_NO, false);
		return ;
	}
	while (data->line[lex_struct.c_pos])
	{
		if (ft_isspace(data->line[lex_struct.c_pos]))
			lex_struct.c_pos += 1;
		else if (ft_ismeta(data->line[lex_struct.c_pos]))
			lexer_meta(data, &lex_struct);
		else
			lexer_word(data, &lex_struct);
	}
}
