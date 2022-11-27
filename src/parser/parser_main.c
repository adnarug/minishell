/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/27 14:47:46 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*\
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
< test2 grep hi | wc -w > test2_result

Para domingo:


Liberar listas y objetos qu eno necessitemos
actualizar en cada sublist que solo hay un comando

*/
/*
< test2 < tedt3 grep hi >> '$USER' | wc -w > $HOME | echo >> '$USER'  "$USER"
 grep hi | wc 

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
	//t_sublist_prs_tok sub_list_pars;
	int i = 0;
	if (!data->list.head) //we had no input and/or the list of tokens is empty
	{
		printf("no tokens to parse\n");
		return ;
	}
	//printf("Numero de pipes en ft parser = %i\n", data->number_pipes);
	data->array_sublist = (t_sublist_prs_tok **)malloc(sizeof(t_sublist_prs_tok *) * (data->number_pipes + 2));
	if (!data->array_sublist)
	{
		printf("error malloc in the array of list\n");
		return ;
	}
	current = data->list.head;//run through list of tokens. 
	while (current) //run through list of tokens. 
	{
		//inizizalice_sublist(&sub_list_pars);
		//create_sublist2(&current, &sub_list_pars);
		data->array_sublist[i] = create_sublist(&current);
		//printf("crea una segunda sublista??\n");
		// here there should be a free function or exit if there i sa probelm
		if (!data->array_sublist[i])
			delete_array_parsedtk(data);
		i++;
	}
	//printf("nulltermina el array??\n");
	data->array_sublist[i] = NULL;
}
