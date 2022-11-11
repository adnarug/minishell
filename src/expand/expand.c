/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:25:54 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/11 10:48:39 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// minishell $ 0$USER >>> de alguna manera esta impriemdno al detras de user
// char *compare_env_list(t_minishell *data, char *env_var)
// {
// 	//funcin para comprar un dato en una lista enlazada y que devuelva el valor. Seguir por aqui lunes por  latarde
// }
// 0$USER9
/*
	Find the key value, 
	compare to the values of env list,
	if find it in the list substitute
	otherwise returns 0
	We pass the pointer to the adress of the string
*/
char	*expand_variable(t_minishell *data , char *buf, char **s)
{
	char	*env_var; //aqui guardaremos la expansion
	char	*var_expanded;
	t_env	*node_env;
	
	char	*ptr = *s;
	env_var = NULL;
	while (*ptr)
	{

		if (is_not_end_expand(*ptr))
		{
			//printf("en if, char: %c \n", *ptr);	
			env_var = ft_strjoin_char(env_var, *ptr);
			//printf("hasta aqui exapnd 2.1 \n");
		}
		else
		{
			//printf("antes del break, char: %c \n", *ptr);
			//printf("hasta aqui exapnd 2 \n");
			break;
		}
		ptr++;
	}
	//printf("hasta aqui exapnd *pointer: %c \n", *ptr);
	*s = --ptr;
	//printf(" *pointer decrementado: %c \n", *ptr);
	node_env = ft_lst_find(data->env_lst, env_var);

	if(!node_env)
	{
			//printf("valor  nullo:\n");
			return("");
	}
	else
	{
		//printf("valor: %s\n", node_env->value);
		return(node_env->value);
	}
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
	new_buff = ft_strdup(""); //atencio que habra que hacer free en algun momento
	while (*s)
	{
		//printf("hasta aqui 1\n");
		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
			change_quot_modus(&quote_mod, *s);
		else if (*s == DOLLAR && !quote_mod)
		{
			s++;
			//printf("Kany pointer_posit before %s\n", s);
			value = expand_variable(data, new_buff, &s);
			//printf("2 valor new_buff: %s and value: %s\n", new_buff, value);

			new_buff = ft_strjoin(new_buff, value);
			//printf("2 valor: %s\n", new_buff);
			//printf("and pointer_posit after %s\n", s);
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

//0$USER999

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