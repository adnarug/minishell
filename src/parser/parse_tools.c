/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:21:15 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/27 01:58:40 by fnieves-         ###   ########.fr       */
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
	//Probably i will need to iniziale fd values
	sub_list_pars->first_prs_tok = NULL; //first element of the list of sublists
	sub_list_pars->size_sublist = 0;
	sub_list_pars->number_cmd = 0;
	sub_list_pars->exec_path = NULL;
	sub_list_pars->fd_in = 0; //ask Pavel
	sub_list_pars->fd_out = 0; //ask Pavel
	add_parsedtokns_sublist(current, sub_list_pars);
	return(sub_list_pars);
}


t_prs_tok *find_last_parsedtok(t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok *last;
	
	// if (!sub_list_pars)
	// {
	// 	printf("sublist does not exit, something wrong is happening\n");
	// 	return (NULL);
	// }
	if (!sub_list_pars->first_prs_tok)
	{
		printf("sublist empty. it also shoul dnot happen becaise its covered before\n");
		//return (sub_list_pars);
	}
	last = sub_list_pars->first_prs_tok;
	while (last->next) //while node does not point to null
	{
		last = last->next;
	}
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
	if (!sub_list_pars->first_prs_tok) //sublist is empty
	{
		sub_list_pars->first_prs_tok = parsedtok;
		return ; // we need to check, if we have to return a value
	}
	//otherwise , find the last element and add to the end
	last = find_last_parsedtok(sub_list_pars);
	last->next = parsedtok;
}
