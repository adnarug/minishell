/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:33:32 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 14:24:02 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Return true if find the char which does not 
	finish the expansion var $ (a-Z, 0-9 or _)
*/

int	is_not_end_expand(char c)
{
	return (ft_isalpha(c) || c == '_' || ft_isdigit(c));
}

/*
	Check if char c is space, tab or next line.
*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

/*
	Check if char c is redirection 
	character (> , <)
*/
int	ft_isredirect(char c)
{
	return (c == REDIRECT_IN || c == REDIRECT_OUT);
}

int	ft_ismeta(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/*
	Check if char c is metacharacter (|, > , <)
	or space, tab or next line. 
*/
int	ft_isspecialchar(char c)
{
	return (ft_isspace(c) || ft_ismeta(c));
}
