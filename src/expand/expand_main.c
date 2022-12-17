/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:25:54 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/13 23:33:50 by pguranda         ###   ########.fr       */
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
char	*expand_variable(t_minishell *data, char **s)
{
	char	*env_var;
	t_env	*node_env;
	char	*ptr;

	ptr = *s;
	env_var = NULL;
	if (ft_isdigit(**s))
		return ("");
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
	free(env_var);
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
	char	*itoa;

	s = *s_arr;
	s++;
	if (!*s)
		new_buff = ft_strjoin(old_buf, "$");
	else if (*s == DOLLAR)
		new_buff = ft_strjoin(old_buf, "$$");
	else if (*s == '?')
	{
		itoa = ft_itoa(g_glob_var_exit);
		new_buff = ft_strjoin(old_buf, itoa);
		free(itoa);
	}
	else
		new_buff = ft_strjoin(old_buf, expand_variable(data, &s));
	*s_arr = s;
	free(old_buf);
	old_buf = NULL;
	return (new_buff);
}

/*
	We loop through the string of each token that is type "w".
	new_buff will be the string of the expanded token.
	 We initialize it empty.
	If we find a quotation mark, we change the mode.
	if (change_quot_modus(&quote_mod, *s)
	&& quote_mod && (quote_mod != *s)) >>> If it is
	 fulfilled, it will copy quotes inside
	other quotes, of different type.
	If it finds the $ we switch to another function.
	Any other character will be copied directly (else)
	if (*s) // for everything but $
	(s++ would give a segmentation fault in that case)
		s++;
*/

void	expand_find(t_minishell *data, t_nod_token *current)
{
	char	*s;
	char	quote_mod;
	char	*new_buff;

	quote_mod = 0;
	s = current->name;
	new_buff = ft_strdup("");
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
	free(current->name);
	current->name = new_buff;
	new_buff = NULL;
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
	t_nod_token	*current;

	current = data->list.head;
	while (current)
	{
		if (current->flag == WORD)
			expand_find(data, current);
		current = current->next;
	}
}
