/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:56 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/01 19:55:43 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initializer_lex(t_lexing *lex_struct)
{
	lex_struct->buff = NULL;
	lex_struct->c_pos = 0;
	lex_struct->type = 0;
	// lex_struct->c = '\0'; //we can take out
	// lex_struct->double_quote = 0;
	// lex_struct->simple_quote = 0;
	//lex_struct->quote = 0;
	//lex_struct->ptr = NULL;
}

/*
	Declare and initialize the lex_struct structure
	Delete all spaces at the beginning and end of the line.
	Verify that all double/single quotes are correctly closed.
	We go through the line character per character:
	If it finds a space, go to the next char.
	if it finds |, <, >, <<, >>, it tokenizes them and identifies them as such,
	everything else it converts it into a word and identifies it as a word.
*/


void	ft_lexer(t_minishell *data) //(t_list_token *list, char *line)
{
	t_lexing lex_struct;
	
	data->line = ft_strtrim((const char *)data->line, SPACE_STRNG);
	initializer_lex(&lex_struct);
	if(!are_quote_closed(data))
		print_error_free_exit(data, ERROR_QUOT, QUOTE_MISSING, true);
	//ft_isclose_quote(data, &lex_struct);  //	Maybe we can change the order of execution
	while (data->line[lex_struct.c_pos]) //anador && no hay error
	{
		if (ft_isspace(data->line[lex_struct.c_pos]))
			lex_struct.c_pos += 1;
		else if (ft_ismeta(data->line[lex_struct.c_pos]) ) //uno de los 3 caracateres
			lexer_meta(data, &lex_struct); 
		else
			lexer_word(data, &lex_struct);
	}
	if (!data->lx_error)
		glob_var_exit = (EXIT_FAILURE);
	//system("leaks minishell");
}
 