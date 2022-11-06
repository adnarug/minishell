/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:47:21 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/06 13:48:45 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//creo que cambia de modo quote correctamente
void	change_quot_modus(char *quote, char c)
{
	if (*quote == QUOTE_OFF)
		*quote = c;
	else 
	{
		if ((*quote == SINGLE_QUOTE || *quote == DOUBLE_QUOTE ) && *quote == c)
			*quote = QUOTE_OFF;
	}
}

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
	char temp;
	
	start = &data->line[lex_struct->c_pos];
	end = go_through_word_lex(start); //end es la posicion del metachar
	//temp = *end;
	//end = 0; //lo usamos para
	lex_struct->buff = ft_substr(start, 0,  end - start); //esto daria el string acabado en 0 y no habria que hacer cambios
	//lex_struct->buff = ft_strdup(start); //hay que calcular la posicion de end , para luego aumentar char_pos
	//*end = temp;
	lex_struct->type = WORD;
	new_token = create_tok(lex_struct);
	free(lex_struct->buff);
	lex_struct->buff = NULL;
	add_toke_list(&(data->list), new_token);
	lex_struct->c_pos = lex_struct->c_pos + end - start; //numero de posiciones a a umentar 
}
