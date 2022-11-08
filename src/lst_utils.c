/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:14:36 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/08 10:58:37 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// Felipe List functiones below:

/*
	Add a new token to the end of the list
*/
void add_toke_list(t_list_token *list, t_nod_token *new)
{
	t_nod_token	*last;
	
	// printf("1 token creado\n");
	// print_token(new);
	// print_list(list);
	if (!list) //List does not exist >>> return
		return;

	if (!list->head) //Empty list. Add token
	{
		list->head = new;
		return ;
	}
	//system("leaks minishell");
	last = find_last_node(list);
	last->next = new;
}

/*
	We create a node from the each word,
	separated by a space coming from promt.
	If there is any problem in the operation we return,
	a pointer to NULL
	Returns the pointer to the node.
*/
t_nod_token *create_tok(t_lexing *lex_struct)
{
	t_nod_token *new_tok;
	
	new_tok = (t_nod_token *)malloc(sizeof(t_nod_token));
	if (!new_tok)
		return (NULL);
	new_tok->name = NULL; //do we need to inicializar a null the field word?
	new_tok->next = NULL;
	new_tok->name = ft_strdup(lex_struct->buff); // atencion: free new token name
	if (!new_tok->name)
	{
		free(new_tok); //free . despues de free , se iguala new_tok = NULL?
		new_tok = NULL;
		return (NULL);
	}
	new_tok->flag = lex_struct->type;
	new_tok->simple_quote = lex_struct->simple_quote;
	new_tok->double_quote = lex_struct->double_quote;
	new_tok->quote = lex_struct->quote; //con cual de las 3 anteriores me quedo
	return(new_tok);
}

t_nod_token *find_last_node(t_list_token *list)
{
	t_nod_token	*last;

	if (!list || !list->head)
		return (NULL);
	last = list->head;
	while (last->next)
		last = last->next;
	return (last);
}

void	delete_list(t_list_token *list)
{
	t_nod_token	*del;
	t_nod_token	*current;
	
	if (!list || !list->head)
		return ;
	del = list->head;
	while (del)
	{
		current = del->next;
		free(del->name);
		free(del);
		del = current;
	}
	list->head = NULL;
}

/*
	inizialice values for token list
*/
void init_list_tok(t_list_token *list)
{

	list->head = NULL;
	//printf("till here ft_lexer ok \n");
	list->size = 0;
}
