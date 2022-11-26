/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:46:50 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/26 22:26:18 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//encontramos un pipe

// void	end_sublist_and_add(t_minishell *data, t_sublist_prs_tok *sub_list_pars) //name of function will be not close and . 
// {
// 	t_sublist_prs_tok	*last_sublist;
// 	//last element of sublist should be already and pointing to NULL
// 	//we add to the end of the header of li
// 	if (!data->lst_sublist.first_sublist) //list is empty
// 	{
// 		data->lst_sublist.first_sublist = sub_list_pars;
// 		printf("1st sublist added to the minishell structure\n");
// 		return ;
// 	}
// 	last_sublist = find_last_sublist(&data->lst_sublist);
// 	last_sublist->next_sublist = sub_list_pars;
// 	// If we are in a pipe after , there will be anther sublist
	
// 	//at any point  i need to keep malloc nodes for 
// 	//i have to inicialze values to null in sub_list_pars, to keep the loop for after next pipe (==next sublist)
// } 


/*
	We are in a token with redirecction
	If the next token is not a word, we exit with error
	Else, we create the parsed token, with its own chararacteristics
	 and we add to the sublist
*/
 void creat_parsedtok_redir(t_nod_token **current, t_sublist_prs_tok *sub_list_pars)
{
	t_prs_tok	*parsedtok_redir;

	if ((*current)->next->flag != WORD)
	{
		printf("the redirection has no a word after. Exit and free whart wver you need to free\n");
		exit(1);
	}
	//this could be a generic function > Create node parsed token o r maybe not
	parsedtok_redir = (t_prs_tok *)malloc(sizeof(t_prs_tok));
	if (!parsedtok_redir)
		return ; // where or how do we indicate this error?
	parsedtok_redir->type = (*current)->flag; //it will give one of the redicrecction char
	parsedtok_redir->word = (*current)->next->name;
	parsedtok_redir->cmd_flags = NULL; //this field is not needed, we point to NULL
	parsedtok_redir->next = NULL; //the node will pointer to NULL
	add_parsedtok_sublist(parsedtok_redir, sub_list_pars);
}




void	add_parsedtokns_sublist(t_nod_token **current, t_sublist_prs_tok *sub_list_pars)
{
	
	while (*current && (*current)->flag != PIPE)
	{
		// printf ("comienzo while.\n");
		// print_token(*current);
		if (ft_strchr(REDIRECT, (*current)->flag)) //si enconrtrtamos un redirect, cogeremos el siguiente nodo y lo convertimos en psren token
		{
			creat_parsedtok_redir(current, sub_list_pars);
			printf ("hemos encontrado un redirect.\n"); //we give the list, the beggining of sublist and current of sublist pointing to pipe
			*current = (*current)->next->next; //we will have jooin one node and next in one parsed token.
		}
		// else if ((*current)->flag == PIPE)
		// {
		// 	end_sublist_and_add(data, sub_list_pars);
		// 	// sub_list_pars = create_sublist(); esto la lia
		// }
		else
		{
			printf ("hemos encontrado una palabra.\n");
			creat_parsedtok_cmd(current, sub_list_pars);
			//we will crate the next tken till pipe or redirection, carefull here with current = current->next;
			//pars_tok_comm(data, current, sub_list_pars);
		}

		//*current = (*current)->next;
		//print_token(*current);
	}
	// printf ("end while.\n");
	// print_token(*current);
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
	//while the next token exists and is not a metachar, make a parsed token . while (current->next && !ft_strchr(METACHAR, current->next->flag)) 
	size_array_cmd = count_arguments(*current);
	parsedtok_cmd->cmd_flags = (char **)malloc(sizeof(char *) * (size_array_cmd + 1));
	if (!parsedtok_cmd->cmd_flags)
		return ;
	while (*current && (*current)->flag == WORD) //(*current && !ft_strchr(METACHAR, (*current)->flag))
	{
		// printf ("en creat_parsedtok_cmd. en el while\n"); //aqui se ha dio al carajo . Corregir depsues d ecenar
		// print_token(*current);
		parsedtok_cmd->cmd_flags[i++] = (*current)->name;
		*current = (*current)->next;
	}
	// printf ("en creat_parsedtok_cmd. despues de splitting\n"); //aqui se ha dio al carajo . Corregir depsues d ecenar
	// print_token(*current);
	parsedtok_cmd->cmd_flags[i] = NULL; // es un 0 , un NULL o un '/0'. Null terminamos
	add_parsedtok_sublist(parsedtok_cmd, sub_list_pars);
	printf ("cuenta argumentos 4.\n");
}