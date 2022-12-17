/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:46:50 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/13 15:32:42 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	We are in a token with redirecction
	If the next token is not a word, we exit with REDIR_EMPTY
	If next token expanded is empty, we exit with REDIR_EXPAND_EMPTY.
	Else, we create the redirect parsed token, with its word, 
	 and we add to the end of sublist.
*/
void	creat_prsdtk_redir(t_minishell *data, t_nod_token **current,
		t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_redir;

	if (!(*current)->next || (*current)->next->flag != WORD)
	{
		write(2, REDIR_EMPTY, ft_strlen(REDIR_EMPTY));
		g_glob_var_exit = REDIR_EMPTY_NO;
		data->prs_error = false;
		return ;
	}
	if (!ft_strcmp((*current)->next->name, ""))
	{
		write(2, REDIR_EXPAND_EMPTY, ft_strlen(REDIR_EXPAND_EMPTY));
		g_glob_var_exit = REDIR_EXPAND_EMPTY_NO;
		data->prs_error = false;
		return ;
	}
	parsedtok_redir = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_redir)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	parsedtok_redir->type = (*current)->flag;
	parsedtok_redir->word = (*current)->next->name;
	(*current)->next->name = NULL;
	parsedtok_redir->cmd_flags = NULL;
	parsedtok_redir->next = NULL;
	add_parsedtok_sublist(parsedtok_redir, sub_list_pars);
}

void	parsing_tokens(t_minishell *data, t_nod_token **current,
		t_sublist_prs_tok *sub_list_pars)
{
	while (*current)
	{
		if (ft_strchr(REDIRECT, (*current)->flag))
		{
			creat_prsdtk_redir(data, current, sub_list_pars);
			sub_list_pars->size_sublist += 1;
			if (data->prs_error)
				*current = (*current)->next->next;
			else
				return ;
		}
		else if ((*current)->flag == PIPE)
		{
			*current = (*current)->next;
			break ;
		}
		else
		{
			creat_prsdtk_cmd(data, current, sub_list_pars);
			sub_list_pars->number_cmd += 1;
			sub_list_pars->size_sublist += 1;
		}
	}
}

/*
	Count the numbr of tokens words before a metachar or null
	to allocate the memory for the command parsed token
*/
int	count_arguments(t_nod_token *current)
{
	int	number_argumnents;

	number_argumnents = 0;
	while (current && (!ft_strchr(METACHAR, current->flag)))
	{
		number_argumnents += 1;
		current = current->next;
	}
	return (number_argumnents);
}

/*
	We are in a token with first command.
	We create the parsed token and we add to the sublist.
	WE will add commands to the array of the parsed token,
	till ther is no more tokens or the token is a Metachar.
*/
void	creat_prsdtk_cmd(t_minishell *data, t_nod_token **current,
		t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_cmd;
	int			size_array_cmd;
	int			i;

	i = 0;
	parsedtok_cmd = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_cmd)
		return ;
	parsedtok_cmd->type = COMMAND;
	parsedtok_cmd->word = NULL;
	parsedtok_cmd->next = NULL;
	size_array_cmd = count_arguments(*current);
	parsedtok_cmd->cmd_flags = (char **)
		malloc(sizeof(char *) * (size_array_cmd + 1));
	if (!parsedtok_cmd->cmd_flags)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	while (*current && (*current)->flag == WORD)
	{
		parsedtok_cmd->cmd_flags[i++] = (*current)->name;
		(*current)->name = NULL;
		*current = (*current)->next;
	}
	parsedtok_cmd->cmd_flags[i] = NULL;
	add_parsedtok_sublist(parsedtok_cmd, sub_list_pars);
}
