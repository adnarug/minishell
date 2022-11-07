/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:46:51 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/07 17:32:24 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Knowing that all quotation marks are correctly closed,
	if a first quotation mark is encountered, it switches
	to quotation mark ON mode until it encounters the same
	type of quotation mark and returns to quotation mark OFF mode.
	FAQ
	Is it correct to pass a pointer to a char that is not a string?
	(i.e. not ending in \0)?
*/
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

void	find_2nd_quote(t_minishell *data, t_lexing *lex_struct)
{
	char *point_2nd_quote;
	int pos_2nd_quote;
	char c;
	
	c = data->line[lex_struct->c_pos]; //no sabemos si es simple o doble
	point_2nd_quote = ft_strchr(data->line + lex_struct->c_pos + 1, c);
	if (!point_2nd_quote) //usar funcion strchr
	{
		printf("quote ( %c ) not closed. we have to free and  Salimos\n", c);
		exit(1);
	}
	pos_2nd_quote = point_2nd_quote - data->line - lex_struct->c_pos + 1;
	lex_struct->simple_quote = 0; //este puedo borrar
	lex_struct->quote = 0;
	lex_struct->c_pos = lex_struct->c_pos + pos_2nd_quote - 1; //nos da el lgar de la posicion de la comilla
}

/*
	First check if  every quote is closed
	Function could be also void
*/
void ft_isclose_quote(t_minishell *data, t_lexing *lex_struct)
{
	while (data->line[lex_struct->c_pos])
	{
		if (data->line[lex_struct->c_pos] == SINGLE_QUOTE || data->line[lex_struct->c_pos] == DOUBLE_QUOTE)
		{
			//lex_struct->simple_quote = 1;
			lex_struct->quote = data->line[lex_struct->c_pos]; //asignamos el valor de quote a buscar 
			find_2nd_quote(data, lex_struct); // damos el valor que nos interese , o varios, devuelve la posicion
		}
		lex_struct->c_pos += 1;
	}
	lex_struct->c_pos = 0;
	lex_struct->quote = 0;
}


// int	isclose_singlequot(t_minishell *data, t_lexing *lex_struct)
// {
// 	char *point_2nd_quote;
// 	int pos_2nd_quote;
	
// 	point_2nd_quote = ft_strchr(data->line + lex_struct->c_pos + 1, SINGLE_QUOTE);
// 	if (!point_2nd_quote) //usar funcion strchr
// 	{
// 		printf("single quote not closed. Exit");
// 		exit(1);
// 	}
// 	pos_2nd_quote = point_2nd_quote - data->line - lex_struct->c_pos + 1;
// 	lex_struct->simple_quote = 0;
// 	lex_struct->c_pos = lex_struct->c_pos + pos_2nd_quote;
// }

// void	lexer_word2(t_minishell *data, t_lexing *lex_struct) //funcion antigua
// {
// 	t_nod_token	*new_token;

// 	while(!ft_isspecialchar(data->line[lex_struct->c_pos]) && data->line[lex_struct->c_pos])
// 	{
// 		//printf("antes de join char buff: %s y letra %c \n", lex_struct->buff, *line);
// 		lex_struct->buff = ft_strjoin_char(lex_struct->buff, data->line[lex_struct->c_pos]);
// 		lex_struct->c_pos += 1;
// 	}
// 	//printf("3 LELga a 3: y el buffer es: %s\n", lex_struct->buff);
// 	//system("leaks minishell");
// 	lex_struct->type = WORD; //vamos a usar otra funcion para ver que oerador asignamos
// 	new_token = create_tok(lex_struct);
// 	free(lex_struct->buff);
// 	lex_struct->buff = NULL;
// 	add_toke_list(&(data->list), new_token);
// 	//system("leaks minishell");
// 	//printf("2  de ha anadido list\n");
// }