/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:46:51 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/22 00:30:10 by fnieves-         ###   ########.fr       */
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
 /*
	Recorremos el input para verificar las dobles/simples comillas
	Si encontramos una comilla(s), cambiamos el estatus hasta que 
	volvamos a encontrar la misma comilla(s) y volvamos a cambiar el status
	Si al final char quote es 0, todas las comillas se ha cerrado correctamente
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
	if (quote) //quote active at the end , means quote not closed
		return (0);
	return (1); //quote closed
}

// esta funcion y la de abao no son necesarias 
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
