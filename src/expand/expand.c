/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:25:54 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/08 19:20:38 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// //funcion del examen
// void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
// {
// 	if (begin_list == NULL || *begin_list == NULL)
// 		return;

// 	t_list *cur = *begin_list;
// //	 TODO: commented out, to be reviewed
// 	// if (cmp(cur->data, data_ref) == 0)
// 	// {
// 	// 	*begin_list = cur->next;
// 	// 	free(cur);
// 	// 	ft_list_remove_if(begin_list, data_ref, cmp);
// 	// }
// 	// cur = *begin_list;
// 	// ft_list_remove_if(&cur->next, data_ref, cmp);
// }



// char *compare_env_list(t_minishell *data, char *env_var)
// {
// 	//funcin para comprar un dato en una lista enlazada y que devuelva el valor. Seguir por aqui lunes por  latarde
// }

/*
	Find the key value, 
	compare to the values of env list,
	if find it in the list substitute
	otherwise returns 0
*/
char	*expand_variable(t_minishell *data , char *buf, char *s)
{
	char	*env_var; //aqui guardaremos la expansion
	char	*var_expanded;
	
	env_var = NULL;
	//printf("hasta aqui exapnd 1 \n");
	while (*s)
	{
		if (not_end_expand(*s))
		{
			env_var = ft_strjoin_char(env_var, *s);
			//printf("hasta aqui exapnd 2.1 \n");
		}
		else
			break;
		s++;
	}
	var_expanded = ft_lst_find(data->env_lst, env_var)->value;
	//printf("hasta aqui exapnd 3 \n");
	printf("result of var expanded: %s \n", var_expanded);
	return(var_expanded);
}

/*

*/
void expand_find(t_minishell *data, t_nod_token *current)
{
	char	*s;
	char	quote_mod;
	char	*new_buff;
	char	*value;

	quote_mod = 0;
	s  = current->name;
	new_buff = NULL;
	while (*s)
	{
		//printf("hasta aqui 1\n");
		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
			change_quot_modus(&quote_mod, *s);
		else if (*s == DOLLAR && !quote_mod)
		{
			//printf("hasta aqui 1.2\n");
			value = expand_variable(data, new_buff, ++s);
			new_buff = ft_strjoin(new_buff, value);
		}
		else
		{
			new_buff = ft_strjoin_char(new_buff, *s);
		}
		s++;
	}
	free(current->name); //verificar esto anque creoo que es demasiaod
	// current->name = NULL;
	current->name = new_buff;
	// free(new_buff);
}

/*
	We go through the elements of the list
	If it is a word type node, we send the the node, to be expanded.
	We run through  the string char by char, looking for the $ sign, if we are not in quote mode.
	At the same time, if it is not $, we add each char in a new buffer.
	If we find the dollar , we identify the key (delimited by a-z A-Z _ 0-9 )
	we send that key to enviroment, and if it is found, we replace it and add it to the expanded_buffer
	we continue to run to the end.
*/
//hacerlo con puntero en lugar de la funicon de roman??
void	ft_expand(t_minishell *data)
{
	t_nod_token *current;

	current = data->list.head;
	while (current)
	{
		if (current->flag == WORD)
		{
			expand_find(data, current);
		}
		current = current->next;
	}

}

//0$USER

// void expand_find(t_minishell *data, t_nod_token *current)
// {
// 	char	*s;
// 	char	quote_mod;
// 	char	*new_buff;
// 	char	*value;

// 	quote_mod = 0;
// 	s  = current->name;
// 	new_buff = NULL;
// 	while (*s)
// 	{
// 		//printf("hasta aqui 1\n");
// 		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
// 			change_quot_modus(&quote_mod, *s);
// 		else if (*s == DOLLAR && !quote_mod)
// 		{
// 			//printf("hasta aqui 1.2\n");
// 			value = expand_variable(data, new_buff, ++s);
// 			new_buff = ft_strjoin(new_buff, value);
// 		}
// 		else
// 		{
// 			new_buff = ft_strjoin_char(new_buff, *s);
// 		}
// 		s++;
// 	}
// 	free(current->name); //verificar esto anque creoo que es demasiaod
// 	// current->name = NULL;
// 	current->name = new_buff;
// 	// free(new_buff);
// }