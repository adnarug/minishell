/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:25:54 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/30 18:34:08 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Find the key value, 
	compare to the values of env list,
	if find it in the list substitute
	otherwise returns 0
	We pass the pointer to the adress of the string
*/

char	*expand_variable(t_minishell *data, char *buf, char **s)
{
	char	*env_var;
	t_env	*node_env;
	char	*ptr;

	ptr = *s;
	env_var = NULL;
	(void)buf; //??borrar 
	while (*ptr)
	{
		if (is_not_end_expand(*ptr))
			env_var = ft_strjoin_char(env_var, *ptr);
		else
			break ;
		ptr++;
	}
	*s = --ptr;
	node_env = ft_lst_find(data->env_lst, env_var);
	if (!node_env)
		return ("");
	return (node_env->value);
}

/*
	We perform the expansion after $
	If it finds, '0', add the $ only and  in the previous function
	cannot execute s++, or it will give a seg fault.
	For $?, retrieve the global variable.
	Otherwise it looks for the varivalen in the environment variables,
	if it doesn't find it, it returns the empty string
*/
char	*perform_expansion(t_minishell *data, char *old_buf, char **s_arr)
{
	char	*new_buff;
	char	*s;

	s = *s_arr;
	s++;
	if (*s == '\0')
		new_buff = ft_strjoin_char(old_buf, DOLLAR);
	else if (*s == DOLLAR)
		new_buff = ft_strjoin(old_buf, "$$");
	else if (*s == '?')
		new_buff = ft_strjoin(old_buf, ft_itoa(glob_var_exit));
	else
		new_buff = ft_strjoin(old_buf, expand_variable(data, old_buf, &s));
	*s_arr = s;
	return (new_buff);
}

/*
	We loop through the string of each token that is type "w". 
	new_buff will be the string of the expanded token. We initialize it empty.
	If we find a quotation mark, we change the mode.
	if (change_quot_modus(&quote_mod, *s) && quote_mod && (quote_mod != *s)) >>>
		If it is fulfilled, it will copy quotes inside other quotes, of different type. 
	If it finds the $ we switch to another function.
	Any other character will be copied directly (else)
	
	if (*s) // for everything but $ (s++ would give a segmentation fault in that case)
		s++;

Deleet this
	"'$USER'" For this case : 'fnieves-' 
	if (change_quot_modus(&quote_mod, *s) && quote_mod && (quote_mod != *s)) 
	echo text"'$USER'" ' $USER '   '"'$USER'"'
	grep hi -l >> '$USER' | wc -w >> $HOME1 | echo >> $??
	| cd "$USER" '"'$USER'"' "'$USER'" $$  << $
*/

void	expand_find(t_minishell *data, t_nod_token *current)
{
	char	*s;
	char	quote_mod;
	char	*new_buff;

	quote_mod = 0;
	s = current->name;
	new_buff = ft_strdup(""); //free?
	while (*s)
	{
		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
		{
			if (change_quot_modus(&quote_mod, *s)
				&& quote_mod && (quote_mod != *s))
				new_buff = ft_strjoin_char(new_buff, *s);
		}
		else if (*s == DOLLAR && quote_mod != SINGLE_QUOTE)
			new_buff = perform_expansion(data, new_buff, &s);
		else
			new_buff = ft_strjoin_char(new_buff, *s);
		if (*s)
			s++;
	}
	free(current->name); //verificar 
	current->name = new_buff;
}

/*
	We go through the elements of the list
	If it is a word type node, we send the the node,
	to be expanded. We run through  the string char by char,
	looking for the $ sign, if we are not in quote mode.
	At the same time, if it is not $, we add each 
	char in a new buffer. If we find the dollar , we identify
	the key (delimited by a-z A-Z _ 0-9 ) we send that key to 
	enviroment, and if it is found, we replace it and add it to 
	the expanded_buffer we continue to run to the end.
*/

void	ft_expand(t_minishell *data)
{
	t_nod_token		*current;

	current = data->list.head;
	while (current)
	{
		if (current->flag == WORD)
			expand_find(data, current);
		current = current->next;
	}
}
