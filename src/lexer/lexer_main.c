/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:56 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/06 13:43:34 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initializer_lex(t_lexing *lex_struct)
{
	lex_struct->buff = NULL;
	lex_struct->c_pos = 0;
	lex_struct->c = '\0'; //we can take out
	lex_struct->double_quote = 0;
	lex_struct->simple_quote = 0;
	lex_struct->type = 0;
	lex_struct->quote = 0;
	//lex_struct->ptr = NULL;
}

// por ahi queda un memory leak. En lexer_meta.  valgrind and check
//add modus searching single / double quotes. Despues de comer
void	ft_lexer(t_minishell *data) //(t_list_token *list, char *line)
{
	t_lexing lex_struct;
	
	data->line = ft_strtrim((const char *)data->line, SPACE_STRNG);
	initializer_lex(&lex_struct);
	ft_isclose_quote(data, &lex_struct); //check if quites are properly closed
	while (data->line[lex_struct.c_pos]) //anador && no hay error
	{
		if (ft_isspace(data->line[lex_struct.c_pos]))
			lex_struct.c_pos += 1;
		else if (ft_ismeta(data->line[lex_struct.c_pos]) ) //uno de los 3 caracateres
			lexer_meta(data, &lex_struct); 
		else
			lexer_word(data, &lex_struct);
	}
	//system("leaks minishell");
}
 /*
Parte de las comillas  para agregar 
		else if (data->line[lex_struct.c_pos] == SINGLE_QUOTE && lex_struct.quote == SINGLE_QUOTE ||
				data->line[lex_struct.c_pos] == SINGLE_QUOTE && !lex_struct.quote)
		{
			if (!lex_struct.quote) //encontramo single quote y estamos en modo no quote >> actiavmos modo
				lex_struct.quote = SINGLE_QUOTE;
			else //ebconrtamos single quote y estamos en modo single quote >>> Desactivamos
				lex_struct.quote = 0;
			lex_struct.c_pos += 1;
		} //------------
		else if (data->line[lex_struct.c_pos] == DOUBLE_QUOTE && lex_struct.quote == DOUBLE_QUOTE ||
				data->line[lex_struct.c_pos] == DOUBLE_QUOTE && !lex_struct.quote)
		{
			if (!lex_struct.quote) //encontramo doub quote y estamos en modo no quote >> actiavmos modo
				lex_struct.quote = DOUBLE_QUOTE;
			else //ebconrtamos doub quote y estamos en modo double quote >>> Desactivamos
				lex_struct.quote = 0;
			lex_struct.c_pos += 1;
		}



para pruebas
 mi > mama|< me <mima >>yo 'amo'>> ||<<
  | > >> < << hola
 | > >> <  hola

feli'mimimi'mamama''mumu | lalala  --> 3 words
fel 'mimimi' mamama''mumu --> 3 words

bash-3.2$ mi
mimamame
bash-3.2$ echo 'mimama'me
mimamame
bash-3.2$ echo 'mimama'|me
bash: me: command not found
bash-3.2$ echo "mimi"mama
mimimama
bash-3.2$ echo "mimi" mama
mimi mama
bash-3.2$ 
bash-3.2$ 'mi' mama
bash: mi: command not found
bash-3.2$ 'mi'mama
bash: mimama: command not found
bash-3.2$ echo 'mi''mama'
mimama
bash-3.2$ echo 'mi''mama' me
mimama me
bash-3.2$ echo 'mi''mama' 'me' 
mimama me
echo 'mi''" a'
 */