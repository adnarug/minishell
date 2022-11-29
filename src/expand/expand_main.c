/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:25:54 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/29 17:27:06 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Find the key value, 
	compare to the values of env list,
	
	if find it in the list substitute
	otherwise returns 0
	We pass the pointer to the adress of the string
	$$ >> no funciona , verificar
	< test2 < tedt3 grep hi >> '$USER' | wc -w > $HOME | echo >> $? | cd $$ << $
	"'$USER'"
	'"$USER mi mama"'
	"'$USER mi papa'" >>> comillas dento de comillas no quitar las comillas. Mirar en expansion
*/

// 
char	*expand_variable(t_minishell *data , char *buf, char **s)
{
	char	*env_var; //aqui guardaremos la expansion
	// char	*var_expanded;
	t_env	*node_env;
	
	char	*ptr = *s;
	env_var = NULL;
	(void)buf;
	while (*ptr)
	{
		if (is_not_end_expand(*ptr))
			env_var = ft_strjoin_char(env_var, *ptr);
		else
			break;
		ptr++;
	}
	*s = --ptr;
	node_env = ft_lst_find(data->env_lst, env_var);
	if(!node_env)
			return("");
	else
		return(node_env->value);
}

/*
SI ENCONTRAMOS UNA COMILLA DENTRO DE OTRAS CIOMILLAS , NO LAS QUITAMOS 
"'$USER'" For this case : if (change_quot_modus(&quote_mod, *s) && quote_mod && (quote_mod != *s)) 
'fnieves-'
echo text"'$USER'" ' $USER '   '"'$USER'"'
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
		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
		{
			if (change_quot_modus(&quote_mod, *s) && quote_mod && (quote_mod != *s)) //what if we leav just like  if (quote_mod && (quote_mod != *s)) ??
				new_buff = ft_strjoin_char(new_buff, *s);
		}
		else if (*s == DOLLAR && quote_mod != SINGLE_QUOTE) // in single quote we do not expand
		{
			s++;
			if (*s == DOLLAR) //we find $$
				value = ft_strdup("$$");
			else if (*s == '\0') //we find $
			{
				new_buff = ft_strjoin_char(new_buff, DOLLAR);
				break; //no podemos continuar o nos metemos en un seg fault
			}
			else if (*s == '?') //we find $?
				value = ft_itoa(glob_var_exit);
			else
				value = expand_variable(data, new_buff, &s);	
			new_buff = ft_strjoin(new_buff, value);
		}
		else
			new_buff = ft_strjoin_char(new_buff, *s);
		s++;
	}
	free(current->name); //verificar esto anque creoo que es demasiaod
	current->name = new_buff;
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
