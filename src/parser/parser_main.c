/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/26 00:04:35 by fnieves-         ###   ########.fr       */
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
*/



//encontramos un pipe

void	end_sublist_and_add(t_minishell *data, t_sublist_prs_tok *sub_list_pars) //name of function will be not close and . 
{
	t_sublist_prs_tok	*last_sublist;
	//last element of sublist should be already and pointing to NULL
	//we add to the end of the header of li
	if (!data->lst_sublist.first_sublist) //list is empty
	{
		data->lst_sublist.first_sublist = sub_list_pars;
		printf("1st sublist added to the minishell structure\n");
		return ;
	}
	last_sublist = find_last_sublist(&data->lst_sublist);
	last_sublist->next_sublist = sub_list_pars;
	//at any point  i need to keep malloc nodes for 
	//i have to inicialze values to null in sub_list_pars, to keep the loop for after next pipe (==next sublist)
} 


/*
	We are in a token with redirecction
	If the next token is not a word, we exit with error
	Else, we create the parsed token, with its own chararacteristics
	 and we add to the sublist
*/
 void creat_parsedtok_redir(t_nod_token *current, t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_redir;

	if (current->next->flag != WORD)
	{
		printf("the redirection has no a word after. Exit and free whart wver you need to free\n");
		exit(1);
	}
	//this could be a generic function > Create node parsed token o r maybe not
	parsedtok_redir = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_redir)
		return ; // where or how do we indicate this error?
	parsedtok_redir->type = current->flag; //it will give one of the redicrecction char
	parsedtok_redir->word = current->next->name;
	parsedtok_redir->cmd_flags = NULL; //this field is not needed, we point to NULL
	parsedtok_redir->next = NULL; //the node will pointer to NULL
	add_parsedtok_sublist(parsedtok_redir, sub_list_pars);
}



/*
	main function for parsing
	Vamos a intentar que funcione la creacion de la nueva lisa con un solo redirecttcion y un command
	necesitanos imprimir la lista de listas
	//despues de comer viernes, hacer la simulacion mental de: < test2 grep hi | wc
< test2 grep hi | wc -w > $HOME | echo >> '$USER'  "$USER"

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
void ft_parser(t_minishell *data)
{

	t_nod_token *current ;//to run throug list of  tokens not parsed
	t_sublist_prs_tok *sub_list_pars; //primera sublista

	// if (!&data->lst_sublist) //do i have to check also !data->list ?
	// {
	// 	printf("we start to parse and the list ob sublist is not initizalice , extrange\n");
	// 	return ; //emppty list (shoudl not really happen at this point)
	// }
	current = data->list.head;
	sub_list_pars = create_sublist(); //we malloc first sublist. Firts node list
	while (current) //run through list of tokens. 
	{
		if (ft_strchr(REDIRECT, current->flag)) //si enconrtrtamos un redirect, cogeremos el siguiente nodo y lo convertimos en psren token
		{
			creat_parsedtok_redir(current, sub_list_pars); //we give the list, the beggining of sublist and current of sublist pointing to pipe
			current = current->next; //we will have jooin one node and next in one parsed token.
		}
		else if (current->flag == PIPE)
		{
			end_sublist_and_add(data, sub_list_pars);
			//a la sublista se le pone un null, se anade a la lista principal al final, y se crea la siguiente sublist. 
		}
		else
		{
			printf ("hemos encontrado una palabra. De momento no anadimos\n");
			//we will crate the next tken till pipe or redirection, carefull here with current = current->next;
			//pars_tok_comm(data, current, sub_list_pars);
		}
		current = current->next;
	}
	//hay que cerrar la lista si no hemos encontrado un pipe
	print_list_parsedtoken(data);
}

// if we did not find a pipe,
//if we got to NULL we need to create the last list before pipe , so the last 2 cases are ok
//a.  check if the list of lists is empty. This will tell us if we need to create another sublist just with one single command with no pipe
//b. list of lists it was not empty, so we got to the current and we can start the execution or the checker, of the grammas , like  
