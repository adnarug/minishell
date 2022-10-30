/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:53 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/30 15:20:46 by fnieves          ###   ########.fr       */
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
	Check if char c is metacharacter (|, > , <)
*/
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