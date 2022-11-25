/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/24 19:30:13 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*\
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
< test2 grep hi | wc -w > test2_result

1. Recorremos la lista y comenzamos a hacer parsed tokesn, if we find a pipe es null de la lista  , y un redirect, hara un nodo ,

If we find pipe >>> current o first list . Despues de ocmer
2. De esta sublista, buscamos todos los redirections y los agriupamos con su palabra 
    a la izquierda. Si un redirection no tiene palabra >>> exit y error
3. El resto tiene que ir en el array

< test2 grep hi | wc -w > test2_result | echo >> test3_result

Elemnt: 0, value= Meta, type = <. 
Elemnt: 1, value= test2, type = w. 
Elemnt: 2, value= grep, type = w. 
Elemnt: 3, value= hi, type = w. 
Elemnt: 4, value= Meta, type = |. 
Elemnt: 5, value= wc, type = w. 
Elemnt: 6, value= -w, type = w. 
Elemnt: 7, value= Meta, type = >. 
Elemnt: 8, value= test2_result, type = w. 
Elemnt: 9, value= Meta, type = |. 
Elemnt: 10, value= echo, type = w. 
Elemnt: 11, value= Meta, type = +. 
Elemnt: 12, value= test3_result, type = w.   
*/

static void add_parsedtok_sublist(t_prs_tok *parsedtok_redir, t_header_prs_tok *sub_list_pars)
{
	t_prs_tok *last;

	if (!sub_list_pars)
	{
		printf("sub_list_pars does not exit. Check, because this should not happen \n");
		exit(1);
	}
	if (!sub_list_pars->prs_tok) //sublist is empty
	{
		sub_list_pars->prs_tok = parsedtok_redir;
		return ; // we need to check, if we have to return a value
	}
	//otherwise , find the last element and add to the end
	last = find_last_parsedtok_sublist(sub_list_pars);
	last->next = parsedtok_redir;
	return ; //check if we need to return anythin 
}



/*
	We are in a token with redirecction
	If the next token is not a word, we exit with error
	Else, we create the parsed token, and we add to the sublist
*/
static void creat_parsedtok_redir(t_minishell *data, t_nod_token *current, t_header_prs_tok *sub_list_pars)
{
	t_prs_tok *parsedtok_redir;

	if (current->next->flag != WORD)
	{
		printf("the redirection has no a word after. Exit and free whart wver you need to free\n");
		exit(1);
	}
	parsedtok_redir = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_redir)
		return ; // where or how do we indicate this error?
	parsedtok_redir->type = current->flag; //it will give one of the redicrecction char
	parsedtok_redir->word = current->next->name;
	parsedtok_redir->word = NULL; //this field is not needed, we point to NULL
	parsedtok_redir->next = NULL; //the node will pointer to NULL
	add_parsedtok_sublist(parsedtok_redir, sub_list_pars);
}

static t_header_prs_tok *create_sublist(void)
{
	t_header_prs_tok *sub_list_pars;
	
	sub_list_pars = (t_header_prs_tok  *)malloc(sizeof(t_header_prs_tok)); //we malloc first sublist
	if(!sub_list_pars)
		return (NULL);
	//do i need to inizialice the values??
	sub_list_pars->next = NULL;
	return(sub_list_pars);

}

/*
	main function for parsing
	Vamos a intentar que funcione la creacion de la nueva lisa con un solo redirecttcion y un command
	necesitanos imprimir la lista de listas
*/
void ft_parser(t_minishell *data)
{

	t_nod_token *current;//to run throug list

	t_header_prs_tok *sub_list_pars;

	if (!data->list.head ) //do i have to check also !data->list ?
		return (NULL); //emppty list (shoudl not really happen at this point)
	
	current = data->list.head;
	sub_list_pars = create_sublist(); //we malloc first sublist
	while (current)
	{
		if (ft_strchr(REDIRECT, current->flag)) //si enconrtrtamos un redirect, cogeremos el siguiente nodo y lo convertimos en psren token
		{
			creat_parsedtok_redir(data, current, sub_list_pars); //we give the list, the beggining of sublist and current of sublist pointing to pipe
			current = current->next; //we will have jooin one node and next in one parsed token.
		}
		else if (current->flag == PIPE)
		{
			close_and_add_sublist(data, sub_list_pars);
			//a la sublista se le pone un null, se anade a la lista principal y se crea la siguiente lista 
		}
		else
		{
			printf ("hemos encontrado una palabra");
			//pars_tok_comm(data, current, sub_list_pars);
		}
		current = current->next;
	}
}

// if we did not find a pipe,
//if we got to NULL we need to create the last list before pipe , so the last 2 cases are ok
//a.  check if the list of lists is empty. This will tell us if we need to create another sublist just with one single command with no pipe
//b. list of lists it was not empty, so we got to the current and we can start the execution or the checker, of the grammas , like  
