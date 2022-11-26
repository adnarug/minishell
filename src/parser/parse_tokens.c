/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:46:50 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/26 12:50:28 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//encontramos un pipe

void	end_sublist_and_add(t_minishell *data, t_sublist_prs_tok *sub_list_pars) //name of function will be not close and . 
{
	t_sublist_prs_tok	*last_sublist;
	//last element of sublist should be already and pointing to NULL
	//we add to the end of the header of li
	if (!data->lst_sublist.first_sublist) //list is empty
	{
		data->lst_sublist.first_sublist = sub_list_pars;
		printf("1st sublist added to the minishell structure\n");
		return ;
	}
	last_sublist = find_last_sublist(&data->lst_sublist);
	last_sublist->next_sublist = sub_list_pars;
	// If we are in a pipe after , there will be anther sublist
	
	//at any point  i need to keep malloc nodes for 
	//i have to inicialze values to null in sub_list_pars, to keep the loop for after next pipe (==next sublist)
} 


/*
	We are in a token with redirecction
	If the next token is not a word, we exit with error
	Else, we create the parsed token, with its own chararacteristics
	 and we add to the sublist
*/
 void creat_parsedtok_redir(t_nod_token *current, t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_redir;

	if (current->next->flag != WORD)
	{
		printf("the redirection has no a word after. Exit and free whart wver you need to free\n");
		exit(1);
	}
	//this could be a generic function > Create node parsed token o r maybe not
	parsedtok_redir = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_redir)
		return ; // where or how do we indicate this error?
	parsedtok_redir->type = current->flag; //it will give one of the redicrecction char
	parsedtok_redir->word = current->next->name;
	parsedtok_redir->cmd_flags = NULL; //this field is not needed, we point to NULL
	parsedtok_redir->next = NULL; //the node will pointer to NULL
	add_parsedtok_sublist(parsedtok_redir, sub_list_pars);
}

/*
	We are in a token with redirecction
	If the next token is not a word, we exit with error
	Else, we create the parsed token, with its own chararacteristics
	 and we add to the sublist
*/
 void creat_parsedtok_cmd(t_nod_token *current, t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_cmd;

	parsedtok_cmd = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_cmd)
		return ; // where or how do we indicate this error?
	parsedtok_cmd->type = COMMAND;
	parsedtok_cmd->word = NULL; //this filed will not be used for comand
	parsedtok_cmd->next = NULL; //the node will pointer to NULL
	parsedtok_cmd->cmd_flags = ??; 
	//while the next token exists and is not a metachar, make a parsed token . while (current->next && !ft_strchr(METACHAR, current->next->flag)) 
	while (current->next && !ft_strchr(METACHAR, current->next->flag))
	{
		
	}

	//this could be a generic function > Create node parsed token o r maybe not
	// parsedtok_cmd = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	// if (!parsedtok_redir)
	// 	return ; // where or how do we indicate this error?
	parsedtok_cmd->word = current->next->name;
	parsedtok_cmd->cmd_flags = NULL; //this field is not needed, we point to NULL
	parsedtok_cmd->next = NULL; //the node will pointer to NULL
	add_parsedtok_sublist(parsedtok_cmd, sub_list_pars);
}
