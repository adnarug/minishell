/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:46:51 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/28 21:37:59 by fnieves-         ###   ########.fr       */
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

bool	change_quot_modus2(char *quote, char c)
{

	if (*quote == QUOTE_OFF)
	{
		*quote = c;
		return true; // el modo se ha cambiado
	}
	else 
	{
		if ((*quote == SINGLE_QUOTE || *quote == DOUBLE_QUOTE ) && *quote == c)
			*quote = QUOTE_OFF;
		return true; // el modo se ha cambiado
	}
	return false; // el modo no se ha cambiado, se trata de quotes dentro de otros quotes
}

 /*
	We scroll through the input to check for double/single quotation marks.
	If we find a quote(s), we change the status until we find the same quote(s)
	and change the status again. 
	If at the end char quote is 0, all quotes have been closed correctly.
 */
int are_quote_closed(t_minishell *data)
{
	char *ptr;

	char quote;
	quote = 0;
	ptr = data->line;
	while (*ptr)
	{
		if (*ptr == SINGLE_QUOTE || *ptr == DOUBLE_QUOTE )
			change_quot_modus(&quote, *ptr);
		ptr++;
	}
	if (quote)
		return (0);
	return (1);
}

// 2 fucntions below not needed
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
	//lex_struct->simple_quote = 0; //este puedo borrar
	lex_struct->quote = 0;
	lex_struct->c_pos = lex_struct->c_pos + pos_2nd_quote - 1; //nos da el lgar de la posicion de la comilla
}

/*
	First check if  every quote is closed
*/

void ft_isclose_quote(t_minishell *data, t_lexing *lex_struct) //esta funcion y la de arriba las podemos quitar
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
