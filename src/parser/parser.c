/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/20 01:09:34 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Vamos a crear una lista con un nodo con cada elemento de la linea

// t_env **ft_parse(char *line)
// {
// 	t_env **lst; //puntero a lista enlazada
// 	return(lst);
// }
void init_list_token(t_list_token *list)
{
	list = NULL;
	list->size = 1;
}

void	creat_lst_tok(t_list_token *list, char *line)
{
	
}


void ft_parser(char *line)
{
	t_list_token list; // pasamos esto &*
	
	init_list_token(&list);
	creat_lst_tok(&list, line);
	printf("imprime linea en programa: %s\n", line);
}