/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:46:51 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 13:59:27 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Knowing that all quotation marks are correctly closed,
	if a first quotation mark is encountered, it switches
	to quotation mark ON mode until it encounters the same
	type of quotation mark and returns to quotation mark OFF mode.
*/

int	change_quot_modus(char *quote, char c)
{
	if (*quote == QUOTE_OFF)
	{
		*quote = c;
		return (1);
	}
	else
	{
		if ((*quote == SINGLE_QUOTE || *quote == DOUBLE_QUOTE)
			&& *quote == c)
			*quote = QUOTE_OFF;
		return (1);
	}
	return (0);
}

/*
	We scroll through the input to check for 
	double/single quotation marks.
	If we find a quote(s), we change the status
	until we find the same quote(s)
	and change the status again. 
	If at the end char quote is 0,
	all quotes have been closed correctly.
*/
int	are_quote_closed(t_minishell *data)
{
	char	*ptr;
	char	quote;

	quote = 0;
	ptr = data->line;
	while (*ptr)
	{
		if (*ptr == SINGLE_QUOTE || *ptr == DOUBLE_QUOTE)
			change_quot_modus(&quote, *ptr);
		ptr++;
	}
	if (quote)
		return (0);
	return (1);
}
