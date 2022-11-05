/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:46:51 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/05 20:05:25 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer_word2(t_minishell *data, t_lexing *lex_struct) //funcion antigua
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

//creo que cambia de modo quote correctamente
void	change_quot_modus(char *quote, char c)
{
	if (*quote == QUOTE_OFF)
		*quote = c;
	else 
	{
		if ((*quote == SINGLE_QUOTE || *quote == DOUBLE_QUOTE ) && *quote == c)
			*quote = QUOTE_OFF;
	}
}

char *go_through_word_lex(char *s)
{
	char quote;

	quote = QUOTE_OFF;
	while (*s)
	{
		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
			change_quot_modus(&quote, *s);
		else if (ft_strchr(DELIMITERS, *s) && !quote) //Is the char one of the delimters? 
			break;
		s++;
	}
	return(s);
	
}

/*
	char pointed is the  start of a word.
	End , receive a pointer to the end of a word " \t|<>" or '\0'
	We copy in the buffer 
*/
void	lexer_word(t_minishell *data, t_lexing *lex_struct)
{
	t_nod_token	*new_token;
	char *start;
	char *end;
	char temp;
	
	start = &data->line[lex_struct->c_pos];

	end = go_through_word_lex(start); //end es la posicion del metachar
	//temp = *end;
	//end = 0; //lo usamos para
	lex_struct->buff = ft_substr(start, 0,  end - start); //esto daria el string acabado en 0 y no habria que hacer cambios
	//lex_struct->buff = ft_strdup(start); //hay que calcular la posicion de end , para luego aumentar char_pos
	//*end = temp;
	//printf("ft_lexer 1\n");
	lex_struct->type = WORD;
	//printf("ft_lexer 2\n");
	new_token = create_tok(lex_struct);
	//printf("ft_lexer 3\n");
	free(lex_struct->buff);
	lex_struct->buff = NULL;
	add_toke_list(&(data->list), new_token);
	//printf("ft_lexer 4\n");
	lex_struct->c_pos = lex_struct->c_pos + end - start; //numero de posiciones a a umentar 
	
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

/*
	First check if  every quote is closed
	void	lexer_meta(t_minishell *data, t_lexing *lex_struct)

*/
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



void	find_2nd_quote(t_minishell *data, t_lexing *lex_struct)
{
	char *point_2nd_quote;
	int pos_2nd_quote;
	char c;
	
	c = data->line[lex_struct->c_pos]; //no sabemos si es simple o doble
	point_2nd_quote = ft_strchr(data->line + lex_struct->c_pos + 1, c);
	if (!point_2nd_quote) //usar funcion strchr
	{
		printf("quote ( %c ) not closed. we have to free and  Salimos\n", c);
		exit(1);
	}
	pos_2nd_quote = point_2nd_quote - data->line - lex_struct->c_pos + 1;
	lex_struct->simple_quote = 0; //este puedo borrar
	lex_struct->quote = 0;
	lex_struct->c_pos = lex_struct->c_pos + pos_2nd_quote - 1; //nos da el lgar de la posicion de la comilla
}

/*
	First check if  every quote is closed
	Function could be also void
*/
void ft_isclose_quote(t_minishell *data, t_lexing *lex_struct)
{
	while (data->line[lex_struct->c_pos])
	{
		if (data->line[lex_struct->c_pos] == SINGLE_QUOTE || data->line[lex_struct->c_pos] == DOUBLE_QUOTE)
		{
			//lex_struct->simple_quote = 1;
			lex_struct->quote = data->line[lex_struct->c_pos]; //asignamos el valor de quote a buscar 
			find_2nd_quote(data, lex_struct); // damos el valor que nos interese , o varios, devuelve la posicion
		}
		lex_struct->c_pos += 1;
	}
	lex_struct->c_pos = 0;
	lex_struct->quote = 0;
}



// int	isclose_singlequot(t_minishell *data, t_lexing *lex_struct)
// {
// 	char *point_2nd_quote;
// 	int pos_2nd_quote;
	
// 	point_2nd_quote = ft_strchr(data->line + lex_struct->c_pos + 1, SINGLE_QUOTE);
// 	if (!point_2nd_quote) //usar funcion strchr
// 	{
// 		printf("single quote not closed. Exit");
// 		exit(1);
// 	}
// 	pos_2nd_quote = point_2nd_quote - data->line - lex_struct->c_pos + 1;
// 	lex_struct->simple_quote = 0;
// 	lex_struct->c_pos = lex_struct->c_pos + pos_2nd_quote;
// }