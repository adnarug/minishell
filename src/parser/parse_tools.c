/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:21:15 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/30 01:12:49 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



//maloqueanndo
t_sublist_prs_tok *create_sublist(t_nod_token **current) //corregido a array
{
	t_sublist_prs_tok *sub_list_pars;
	
	sub_list_pars = (t_sublist_prs_tok  *)malloc(sizeof(t_sublist_prs_tok)); //we malloc first sublist
	if(!sub_list_pars)
		return (NULL);
	sub_list_pars->prs_tok = NULL; //first element of the list of sublists
	sub_list_pars->size_sublist = 0;
	sub_list_pars->number_cmd = 0;
	sub_list_pars->exec_path = NULL;
	sub_list_pars->fd_in = 0; //ask Pavel
	sub_list_pars->fd_out = 0; //ask Pavel
	parsing_tokens(current, sub_list_pars);
	return(sub_list_pars);
}


t_prs_tok *find_last_parsedtok(t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok *last;
	
	if (!sub_list_pars->prs_tok)
	{
		printf("sublist empty. it also shoul dnot happen becaise its covered before\n");
		//return (sub_list_pars); // exit
	}
	last = sub_list_pars->prs_tok;
	while (last->next) //while node does not point to null
		last = last->next;
	return (last);
}


/*
  Add parsed tokens to sublits. It could be cmd parsed nodes. For array
  or redirecttion parsed nodes
*/
 void add_parsedtok_sublist(t_prs_tok *parsedtok, t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok *last;

	if (!sub_list_pars)
	{
		printf("sub_list_pars does not exit. Check, because this should not happen \n");
		exit(1);
	}
	if (!sub_list_pars->prs_tok) //sublist is empty
	{
		sub_list_pars->prs_tok = parsedtok;
		return ; // we need to check, if we have to return a value
	}
	last = find_last_parsedtok(sub_list_pars);
	last->next = parsedtok;
}



// to delete!!


// void	print_list_parsedtoken2(t_sublist_prs_tok	*array_sublist)
// {
// 	int i = 0;
// 	t_prs_tok *current_parsedtoken;
// 	//t_sublist_prs_tok	*current_sublist;
// 	printf("\n-------BEGIINING de impresion  list unica of parsed tokens----------\n");
// 	if (!array_sublist)
// 	{
// 		printf("-------El array no apunta a nada----------\n");
// 		printf("-------END from list of parsed tokens----------\n");
// 		return ;
// 	}

// 	int j = 0;
// 	if (!array_sublist)
// 	{
// 		printf("La Subliste %i esta vacia y no deberia imprimir mas\n", i);
// 	}
// 	else //cambia l acondicion
// 	{
// 		printf("Start subliste %i\n", i);
// 		current_parsedtoken = array_sublist->prs_tok;
// 		while (current_parsedtoken)
// 		{
// 			printf("	node %i de Subliste %i. ", j, i);
// 			if (current_parsedtoken->type == COMMAND)
// 			{
// 				printf(" COMMAND: \n");
// 				int k = 0;
// 				//printf("   fuera Argumento %i, comando:|%s| \n",k , current_parsedtoken->cmd_flags[k]);
// 				while (current_parsedtoken->cmd_flags[k])
// 				{
// 					printf("	- Argument %i, command:|%s| \n",k , current_parsedtoken->cmd_flags[k]);
// 					k++;
// 				}
// 			}
// 			else if (ft_strchr(REDIRECT, current_parsedtoken->type))
// 			{
// 				printf(" REDIRECT: |%c| \n	-argument: |%s| \n", current_parsedtoken->type, current_parsedtoken->word);	
// 			}
// 			else
// 				printf("what kind of fucking parsed token are you printing?? \n");
// 			j++;
// 			current_parsedtoken = current_parsedtoken->next;
// 		}
// 	}
// 	printf("\n-------END from list of parsed tokens----------\n");
// }