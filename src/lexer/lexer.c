/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:56 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/31 00:47:43 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer_word(t_minishell *data, t_lexing *lex_struct)
{
	t_nod_token	*new_token;
	
	
	while(!ft_isspecialchar(data->line[lex_struct->c_pos]) && data->line[lex_struct->c_pos])
	{
		//printf("antes de join char buff: %s y letra %c \n", lex_struct->buff, *line);
		lex_struct->buff = ft_strjoin_char(lex_struct->buff, data->line[lex_struct->c_pos]);
		lex_struct->c_pos += 1;
	}
	//printf("3 LELga a 3: y el buffer es: %s\n", lex_struct->buff);
	//system("leaks minishell");
	lex_struct->type = WORD; //vamos a usar otra funcion para ver que oerador asignamos
	new_token = create_tok(lex_struct);
	free(lex_struct->buff);
	lex_struct->buff = NULL;
	add_toke_list(data->list, new_token);
	//system("leaks minishell");
	//printf("2  de ha anadido list\n");
}

/*
	once we find < or >, it will check next char if 
	we have  <<, >>. We will save the info in the 
*/

void	lex_redirect(t_minishell *data, t_lexing *lex_struct)
{
	int	redir_repeted;

	redir_repeted = 0;
	if (data->line[lex_struct->c_pos] == data->line[lex_struct->c_pos + 1])
		redir_repeted = 1;
	if (data->line[lex_struct->c_pos] == REDIRECT_IN)
		lex_struct->type = REDIRECT_IN;
			if (redir_repeted)
				lex_struct->type = HEREDOC;
	else
		lex_struct->type = REDIRECT_OUT;
			if (redir_repeted)
				lex_struct->type = APPEND;
	lex_struct->buff = ft_strjoin_char(lex_struct->buff, data->line[lex_struct->c_pos]);
	lex_struct->c_pos += 1;
	if (redir_repeted)
		lex_struct->c_pos += 1;

}

void	lexer_meta(t_minishell *data, t_lexing *lex_struct)
{
	t_nod_token	*new_token;
	
	if (ft_isredirect(data->line[lex_struct->c_pos]))
	{
		lex_redirect(data, lex_struct);
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
	add_toke_list(data->list, new_token);
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
void	ft_lexer(t_minishell *data) //(t_list_token *list, char *line)
{
	t_lexing lex_struct;
	
	data->line = ft_strtrim((const char *)data->line, " ");
	initializer_lex(&lex_struct);
	//de momento solo words
	
	while (data->line[lex_struct.c_pos]) //anador && no hay error
	{
		//lex_struct.c = *line;
		if (ft_isspace(data->line[lex_struct.c_pos]))
		{
			//printf("en este if no debe entra\n");
			lex_struct.c_pos += 1;
		}
		else if (ft_ismeta(data->line[lex_struct.c_pos])) //uno de los 3 caracateres
		{
			lexer_meta(data, &lex_struct); //seguimos domingo 30 despues de comer. Hacemos una funcion como word para estsp caracteres
		}
		// else if (data->line[lex_struct.c_pos] == SINGLE_QUOTE)
		// {
		// 	lexer_singl_quot(data, &lex_struct);
		// }
		else
		{
			//printf("Entra en word con posicion:%i \n", lex_struct.c_pos);			
			lexer_word(data, &lex_struct);
		}
		// else
		// {
		// 	printf("otros casos");
		// }
	}
	//system("leaks minishell");	
}

//para pruebas
 // mi mama | me <mima >>yo 'amo>> || echo ls