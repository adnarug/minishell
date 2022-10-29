/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:56 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/29 20:24:46 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_strjoin_char(char *buff, char c) //poner esta en libft
{
	char *new_buff;
	int i;

	new_buff = malloc(sizeof(char) * (ft_strlen(buff) + 2));
	if (!new_buff)
		return (NULL);
	i = 0;
	if (buff)
	{
		while (buff[i])
		{
			new_buff[i] = buff[i];
			i++;
		}
	}
	new_buff[i] = c;
	new_buff[i + 1] = '\0';
	free(buff);
	buff = NULL;
	return (new_buff);
}

void	lexer_word(t_list_token *list, t_lexing *lex_struct, char *line)
{
	t_nod_token	*new_token;
	
	lex_struct->type = TYP_WORD;
	while(!ft_isspace(line[lex_struct->c_pos]) && line[lex_struct->c_pos])
	{
		//printf("antes de join char buff: %s y letra %c \n", lex_struct->buff, *line);
		lex_struct->buff = ft_strjoin_char(lex_struct->buff, line[lex_struct->c_pos]);
		lex_struct->c_pos += 1;
	}
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
	
	while (line[lex_struct.c_pos])
	{
		//lex_struct.c = *line;
		if (ft_isspace(line[lex_struct.c_pos]))
		{
			//printf("en este if no debe entra\n");
			lex_struct.c_pos += 1;
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
