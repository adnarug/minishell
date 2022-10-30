/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:56 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/30 17:54:31 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer_word(t_list_token *list, t_lexing *lex_struct, char *line)
{
	t_nod_token	*new_token;
	
	
	while(!ft_isspecialchar(line[lex_struct->c_pos]) && line[lex_struct->c_pos])
	{
		//printf("antes de join char buff: %s y letra %c \n", lex_struct->buff, *line);
		lex_struct->buff = ft_strjoin_char(lex_struct->buff, line[lex_struct->c_pos]);
		lex_struct->c_pos += 1;
	}
	//printf("3 LELga a 3: y el buffer es: %s\n", lex_struct->buff);
	//system("leaks minishell");
	lex_struct->type = TYP_WORD; //vamos a usar otra funcion para ver que oerador asignamos
	new_token = create_tok(lex_struct);
	free(lex_struct->buff);
	lex_struct->buff = NULL;
	add_toke_list(list, new_token);
	//system("leaks minishell");
	//printf("2  de ha anadido list\n");
}

/*
	once we find < or >, it will check next char if 
	we have  <<, >>. We will save the info in the 
*/

void	lex_redirect(t_list_token *list, t_lexing *lex_struct, char *line)
{
	int	redir_repeted;

	redir_repeted = 0;
	if (line[lex_struct->c_pos] == line[lex_struct->c_pos + 1])
		redir_repeted = 1;
	if (line[lex_struct->c_pos] == REDIRECT_IN)
		lex_struct->type = REDIRECT_IN;
			if (redir_repeted)
				lex_struct->type = HEREDOC;
	else
		lex_struct->type = REDIRECT_OUT;
			if (redir_repeted)
				lex_struct->type = APPEND;
	lex_struct->buff = ft_strjoin_char(lex_struct->buff, line[lex_struct->c_pos]);
	lex_struct->c_pos += 1;
	if (redir_repeted)
		lex_struct->c_pos += 1;

}

void	lexer_meta(t_list_token *list, t_lexing *lex_struct, char *line)
{
	t_nod_token	*new_token;
	
	if (ft_isredirect(line[lex_struct->c_pos]))
	{
		lex_redirect(list, lex_struct, line);
	}
	else //find a pipe
	{
		lex_struct->type = PIPE;
		lex_struct->c_pos += 1;
	}
	lex_struct->buff = ft_strdup("Meta"); //ponemos este valor para que creee el nodo

	//printf("3 LELga a 3: y el buffer es: %s\n", lex_struct->buff);
	//system("leaks minishell");
	new_token = create_tok(lex_struct);
	free(lex_struct->buff);
	lex_struct->buff = NULL;
	add_toke_list(list, new_token);
	//system("leaks minishell");
	//printf("2  de ha anadido list\n");
}



void	initializer_lex(t_lexing *lex_struct)
{
	lex_struct->buff = NULL;
	lex_struct->c_pos = 0;
	lex_struct->c = '\0';
	lex_struct->double_quote = 0;
	lex_struct->simple_quote = 0;
	lex_struct->type = 0;
}

// por ahi queda un memory leak
void	ft_lexer(t_list_token *list, char *line)
{
	t_lexing lex_struct;
	
	line = ft_strtrim((const char *)line, " ");
	initializer_lex(&lex_struct);
	init_list_tok(list);
	//de momento solo words
	
	while (line[lex_struct.c_pos]) //anador && no hay error
	{
		//lex_struct.c = *line;
		if (ft_isspace(line[lex_struct.c_pos]))
		{
			//printf("en este if no debe entra\n");
			lex_struct.c_pos += 1;
		}
		else if (ft_ismeta(line[lex_struct.c_pos])) //uno de los 3 caracateres
		{
			lexer_meta(list, &lex_struct, line); //seguimos domingo 30 despues de comer. Hacemos una funcion como word para estsp caracteres
		}
		else
		{
			//printf("Entra en word con posicion:%i \n", lex_struct.c_pos);			
			lexer_word(list, &lex_struct, line);
		}
		// else
		// {
		// 	printf("otros casos");
		// }
	}
	//system("leaks minishell");	
}

//para pruebas
 // mi mama | me <mima >>yo amo>> || echo ls