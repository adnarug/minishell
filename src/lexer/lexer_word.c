/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:47:21 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/02 13:15:22 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *go_through_word_lex(char *s)
{
	char quote;

	quote = QUOTE_OFF;
	while (*s)
	{
		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
			change_quot_modus(&quote, *s);
		else if (ft_strchr(DELIMITERS, *s) && !quote) //Is the char one of the delimters? 
			break;
		s++;
	}
	return(s);
}

/*
	char pointed is the  start of a word.
	End , receive a pointer to the end of a word " \t|<>" or '\0'
	We copy in the buffer 
*/
void	lexer_word(t_minishell *data, t_lexing *lex_struct)
{
	t_nod_token	*new_token;
	char *start;
	char *end;
	
	start = &data->line[lex_struct->c_pos];
	end = go_through_word_lex(start);
	lex_struct->buff = ft_substr(start, 0,  end - start);
	lex_struct->type = WORD;
	new_token = create_tok(lex_struct);
	lex_struct->buff = NULL;
	add_toke_list(&(data->list), new_token);
	lex_struct->c_pos = lex_struct->c_pos + end - start; //numero de posiciones a a umentar 
}
