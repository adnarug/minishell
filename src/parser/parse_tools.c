/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:21:15 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/26 13:52:11 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		add_parsedtokns_sublist(t_nod_token *current, t_sublist_prs_tok *sub_list_pars)
{
	while (current && current->flag != PIPE)
	{
		if (ft_strchr(REDIRECT, current->flag)) //si enconrtrtamos un redirect, cogeremos el siguiente nodo y lo convertimos en psren token
		{
			creat_parsedtok_redir(current, sub_list_pars);
			printf ("hemos encontrado un redirect. anadimos\n"); //we give the list, the beggining of sublist and current of sublist pointing to pipe
			current = current->next; //we will have jooin one node and next in one parsed token.
		}
		// else if (current->flag == PIPE)
		// {
		// 	end_sublist_and_add(data, sub_list_pars);
		// 	// sub_list_pars = create_sublist(); esto la lia
		// }
		else
		{
			printf ("hemos encontrado una palabra. De momento no anadimos\n");
			creat_parsedtok_cmd(current, sub_list_pars);
			//we will crate the next tken till pipe or redirection, carefull here with current = current->next;
			//pars_tok_comm(data, current, sub_list_pars);
		}
		current = current->next;
	}
}


t_sublist_prs_tok *create_sublist(t_nod_token *current)
{
	t_sublist_prs_tok *sub_list_pars;
	
	sub_list_pars = (t_sublist_prs_tok  *)malloc(sizeof(t_sublist_prs_tok)); //we malloc first sublist
	if(!sub_list_pars)
		return (NULL);
	//Probably i will need to iniziale fd values
	sub_list_pars->first_prs_tok = NULL; //first element of the list of sublists
	sub_list_pars->size_sublist = 0;
	sub_list_pars->number_cmd = 0;
	add_parsedtokns_sublist(current, sub_list_pars);
	return(sub_list_pars);
}

/*
	
*/
t_sublist_prs_tok *find_last_sublist(t_head_sublst_parstk	*lst_sublist)
{
	t_sublist_prs_tok	*last_sublist;
	if (!lst_sublist)
	{
		printf("there is no header to sublists. somethinhg did not work\n");
		return (NULL);
	}
	if (!lst_sublist->first_sublist)
	{
		printf("header point to any list. we can add first sublist\n");
		return (lst_sublist->first_sublist);
	}
	last_sublist = lst_sublist->first_sublist;
	while (last_sublist)
	{
		last_sublist = last_sublist->next_sublist;
	}
	return (last_sublist);
}

t_prs_tok *find_last_parsedtok(t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok *last;
	
	if (!sub_list_pars)
	{
		printf("sublist does not exit, something wrong is happening\n");
		return (NULL);
	}
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
  Add parsed tokens to sublits. It could be cmd parsed nodes 
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



//To delete? keep going here

void	print_list_parsedtoken(t_minishell *data)
{
	int i = 0;
	t_prs_tok *current_parsedtoken;
	t_sublist_prs_tok	*current_sublist;
	printf("-------BEGIINING from list of parsed tokens----------\n");
	if (!data->lst_sublist.first_sublist)
	{
		printf("No hay sublistas\n");
		printf("-------END from list of parsed tokens----------\n");
		return ;
	}
	//recorremos las listas
	current_sublist = data->lst_sublist.first_sublist;
	while (current_sublist)
	{
		int j = 0;
		if (!current_sublist->first_prs_tok)
		{
			printf("La Sublista %i esta vacia y no deberia imprimir mas\n", i);
		}
		else
		{
			printf("comienzo de Sublista %i\n", i);
			current_parsedtoken = current_sublist->first_prs_tok;
			while (current_parsedtoken)
			{
				printf(" %i er nodo de Sublista %i. ", j, i);
				printf("  Tipo %c \n", current_parsedtoken->type);
				j++;
				current_parsedtoken = current_parsedtoken->next;
			}
		}
		i++;
		current_sublist = current_sublist->next_sublist;
	}
	printf("-------END from list of parsed tokens----------\n");
}
