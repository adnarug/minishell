/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/24 17:38:55 by fnieves-         ###   ########.fr       */
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


jueveshacer un git status
git restore. Vuelve al principo del commit
Git_ reset_ volvera al ciomit anterior
*/

static void	create_list_pars(t_minishell *data, t_nod_token *ini, t_nod_token *current, int size_sublist)
{
	while (ini && ini != current) //cuando ini apunte a current ( a pipe o NULL??, se acabo)
	{
		
		ini = ini->next;
	}
}

void ft_parser(t_minishell *data)
{

	t_nod_token *current;
	
	t_header_prs_tok *list_parsed;

	if (!data->list.head ) //do i have to check also !data->list ?
		return (NULL); //emppty list (shoudl not really happen at this point)
	current = data->list.head; 
	list_parsed = (t_header_prs_tok  *)malloc(sizeof(t_header_prs_tok));
	if(!list_parsed)
		return (NULL);
	while (current)
	{
		
		if (ft_strchr(REDIRECT, current->flag)) //si enconrtrtamos un redirect, cogeremos el siguiente nodo y lo convertimos en psren token
		{
			 (data, ini, current, size_sublist); //we give the list, the beggining of sublist and current of sublist pointing to pipe
		}
		else if (current->flag == PIPE)
		{
			//la lista se le pone un null y se crea la siguiente lista 
		}
		else
		{
			//un  nodo word
		}
		size_sublist++;
		current = current->next;
	}
	// if we did not find a pipe,
	//if we got to NULL we need to create the last list before pipe , so the last 2 cases are ok
	//a.  check if the list of lists is empty. This will tell us if we need to create another sublist just with one single command with no pipe
	//b. list of lists it was not empty, so we got to the current and we can start the execution or the checker, of the grammas , like  
}