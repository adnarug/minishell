/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:56 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/01 23:36:10 by fnieves-         ###   ########.fr       */
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
	add_toke_list(&(data->list), new_token);
	//system("leaks minishell");
	//printf("2  de ha anadido list\n");
}

/*
	once we find < or >, it will check next char if 
	we have  <<, >>. We will save the info in the 
*/
//this functions is creating leaks 
void	lex_redirect(t_minishell *data, t_lexing *lex_struct)
{
	int	redir_repeted;
	//system("leaks minishell");
	redir_repeted = 0;
	if (data->line[lex_struct->c_pos] == data->line[lex_struct->c_pos + 1])
		redir_repeted = 1;
	//printf(" en lexredirect: %c\n", data->line[lex_struct->c_pos]);
	if (data->line[lex_struct->c_pos] == REDIRECT_IN)
	{
		lex_struct->type = REDIRECT_IN;
			if (redir_repeted)
				lex_struct->type = HEREDOC;
	}
	else
	{		
		lex_struct->type = REDIRECT_OUT;
			if (redir_repeted)
				lex_struct->type = APPEND;
	}
	lex_struct->buff = ft_strjoin_char(lex_struct->buff, data->line[lex_struct->c_pos]);
	lex_struct->c_pos += 1;
	if (redir_repeted)
		lex_struct->c_pos += 1;
	//system("leaks minishell");
}

//esta funcion igual no  hace falta
int ft_isclose_quote(t_minishell *data, t_lexing *lex_struct)
{
	int i;

	i = 1;
	while (data->line[lex_struct->c_pos + i])
	{
		if (data->line[lex_struct->c_pos] == SINGLE_QUOTE)
			return (1);
		i++;
	}
	return (0);
}

void	lexer_singl_quot(t_minishell *data, t_lexing *lex_struct)
{
	//string en la posicion de la primera comill
	char *point_2nd_quote;
	t_nod_token *new_token;
	int pos_2nd_quote;
	
	point_2nd_quote = ft_strchr(data->line + lex_struct->c_pos + 1, SINGLE_QUOTE); //empieza a buscardesde l aprimera comilla
	if (!point_2nd_quote) //usar funcion strchr
	{
		printf("single quote not closed. Exit");
		exit(1);
	}
	pos_2nd_quote = point_2nd_quote - data->line - lex_struct->c_pos + 1;
	//if we want to include ' in the node
	lex_struct->buff = ft_substr(data->line, lex_struct->c_pos, pos_2nd_quote);
	//if we do not want to include ' the word
	//lex_struct->buff = ft_substr(data->line, lex_struct->c_pos + 1 , pos_2nd_quote - 1);
	lex_struct->simple_quote = 1;
	lex_struct->c_pos = lex_struct->c_pos + pos_2nd_quote;
	new_token = create_tok(lex_struct);
	free(lex_struct->buff);
	lex_struct->buff = NULL;
	add_toke_list(&(data->list), new_token);
	lex_struct->simple_quote = 0;
	
	
}

void	lexer_meta(t_minishell *data, t_lexing *lex_struct)
{
	t_nod_token	*new_token;
	
	if (ft_isredirect(data->line[lex_struct->c_pos])) //< or >
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
	add_toke_list(&(data->list), new_token);
	//system("leaks minishell");
	//printf("2  de ha anadido list\n");
}



void	initializer_lex(t_lexing *lex_struct)
{
	lex_struct->buff = NULL;
	lex_struct->c_pos = 0;
	lex_struct->c = '\0'; //we can take out
	lex_struct->double_quote = 0;
	lex_struct->simple_quote = 0;
	lex_struct->type = 0;
}

// por ahi queda un memory leak. Instalar valgrind y verificar
void	ft_lexer(t_minishell *data) //(t_list_token *list, char *line)
{
	t_lexing lex_struct;
	data->line = ft_strtrim((const char *)data->line, " ");
	initializer_lex(&lex_struct);
	//de momento solo words
	//system("leaks minishell");	

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
		else if (data->line[lex_struct.c_pos] == SINGLE_QUOTE)
		{
			lexer_singl_quot(data, &lex_struct);
		}
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
 /*

para pruebas
 mi > mama|< me <mima >>yo 'amo'>> ||<<
  | > >> < << hola
 | > >> <  hola

feli'mimimi'mamama''mumu | lalala  --> 3 words
fel 'mimimi' mamama''mumu --> 3 words

bash-3.2$ echo 'mimama'me
mimamame
bash-3.2$ echo 'mimama'me
mimamame
bash-3.2$ echo 'mimama'|me
bash: me: command not found
bash-3.2$ echo "mimi"mama
mimimama
bash-3.2$ echo "mimi" mama
mimi mama
bash-3.2$ 
bash-3.2$ 'mi' mama
bash: mi: command not found
bash-3.2$ 'mi'mama
bash: mimama: command not found
bash-3.2$ echo 'mi''mama'
mimama
bash-3.2$ echo 'mi''mama' me
mimama me
bash-3.2$ echo 'mi'mama' 'me' 
mimama me
 */