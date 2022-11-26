/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:41 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*\
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
< test2 grep hi | wc -w > test2_result

*/



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
	//t_sublist_prs_tok *sub_list_pars; //primera sublista
	int i = 0;
	
	printf("Numero de pipes en ft parser = %i\n", data->number_pipes);
	data->array_sublist = (t_sublist_prs_tok **)malloc(sizeof(t_sublist_prs_tok *) * (data->number_pipes + 2));
	if (!data->array_sublist)
	{
		printf("error malloc in the array of list\n");
		return ;
	}
	current = data->list.head;
	while (current) //run through list of tokens. 
	{
		data->array_sublist[i] = create_sublist(current);
		current = current->next;
	}
	//hay que cerrar la lista si no hemos encontrado un pipe
	//print_list_parsedtoken(data);
}

// if we did not find a pipe,
//if we got to NULL we need to create the last list before pipe , so the last 2 cases are ok
//a.  check if the list of lists is empty. This will tell us if we need to create another sublist just with one single command with no pipe
//b. list of lists it was not empty, so we got to the current and we can start the execution or the checker, of the grammas , like  
