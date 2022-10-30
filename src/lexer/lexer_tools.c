/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:53 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/30 16:56:59 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Check if char c is space, tab or next line.
*/
int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}


/*
	Check if char c is redirection 
	character (> , <)
*/
int ft_isredirect(char c)
{
	return (c == REDIRECT_IN || c == REDIRECT_OUT);
}

int ft_ismeta(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/*
	Check if char c is metacharacter (|, > , <)
	or space, tab or next line. 
*/
int ft_isspecialchar(char c)
{
	return(ft_isspace(c) || ft_ismeta(c));
}