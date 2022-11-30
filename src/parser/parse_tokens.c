/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:46:50 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/30 01:17:11 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	We are in a token with redirecction
	If the next token is not a word, we exit with error
	Else, we create the parsed token, with its own chararacteristics
	 and we add to the sublist
*/
 void creat_parsedtok_redir(t_nod_token **current, t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_redir;

	if (!(*current)->next || (*current)->next->flag != WORD)
	{
		printf("the redirection |%c| has no a file name after. Exit and free whart wver you need to free\n", (*current)->flag);
		exit(1);
	}
	if (!ft_strcmp((*current)->next->name, ""))
	{
		printf("the redirection |%c| has a word but empty. Exit and free whart wver you need to free\n", (*current)->flag);
		exit(1);
	}
	parsedtok_redir = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_redir)
		return ; // where or how do we indicate this error?
	parsedtok_redir->type = (*current)->flag;
	parsedtok_redir->word = (*current)->next->name;
	parsedtok_redir->cmd_flags = NULL;
	parsedtok_redir->next = NULL; //the node will pointer to NULL
	add_parsedtok_sublist(parsedtok_redir, sub_list_pars); //cambiar nombre por add_parsedtok_sublist
}




void	parsing_tokens(t_nod_token **current, t_sublist_prs_tok *sub_list_pars)
{
	
	while (*current) //(*current && (*current)->flag != PIPE)
	{
		if (ft_strchr(REDIRECT, (*current)->flag)) //si enconrtrtamos un redirect, cogeremos el siguiente nodo y lo convertimos en psren token
		{
			creat_parsedtok_redir(current, sub_list_pars);
			*current = (*current)->next->next; //we will have jooin one node and next in one parsed token.
		}
		else if ((*current)->flag == PIPE)
		{
			*current = (*current)->next;
			break;
		}
		else
		{
			sub_list_pars->number_cmd += 1; //if its not 1 , wiill be an errror
			creat_parsedtok_cmd(current, sub_list_pars);
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
	return(number_argumnents);
}

/*
	We are in a token with command
	Else, we create the parsed token, with its own chararacteristics
	 and we add to the sublist
	 < test.txt  comando1 argumento1
*/
 void creat_parsedtok_cmd(t_nod_token **current, t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_cmd;
	int		size_array_cmd;
	int i = 0;

	parsedtok_cmd = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_cmd)
		return ; // where or how do we indicate this error?
	parsedtok_cmd->type = COMMAND;
	parsedtok_cmd->word = NULL; //this filed will not be used for comand
	parsedtok_cmd->next = NULL; //the node will pointer to NULL
	size_array_cmd = count_arguments(*current);
	parsedtok_cmd->cmd_flags = (char **)malloc(sizeof(char *) * (size_array_cmd + 1));
	if (!parsedtok_cmd->cmd_flags)
		return ;
	while (*current && (*current)->flag == WORD) //(*current && !ft_strchr(METACHAR, (*current)->flag))
	{
		parsedtok_cmd->cmd_flags[i++] = (*current)->name;
		*current = (*current)->next;
	}
	parsedtok_cmd->cmd_flags[i] = NULL; // es un 0 , un NULL o un '/0'. Null terminamos
	add_parsedtok_sublist(parsedtok_cmd, sub_list_pars);
}


