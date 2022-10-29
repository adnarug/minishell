/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:53 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/29 15:10:44 by fnieves-         ###   ########.fr       */
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