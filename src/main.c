/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/23 18:03:01 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
 11/11/22
 Incluir en el nodo de la lista un char para el texto antiguo y para despues de la expansion
 Incluir en el nodo si hay comillas o no . Vermos despues
 echo $ $ >> no hay que expandir
 echo text"$USER" >>> Expandir sin tener en cuenta las "" , also for cd,  cd "$HOME"

 

*/

/*
	tcgetattr(STDOUT_FILENO, &data->termios_default);
	We make a copy of the default atributes of termios
*/

void	initializer_data(t_minishell *data)
{
	data->line = NULL;
	data->list.head = NULL;
	data->list.size = 0;
	data->list_prs.tokens = NULL;
	data->list_prs.next = NULL;
	data->list_prs.size = 0;
	tcgetattr(STDOUT_FILENO, &data->termios_default);
}

/*
	atexit(check_leaks);
*/
void	check_leaks(void)
{
	system("leaks minishell");
}

void debuggear(t_minishell *data)
{
	data->line = ft_strdup("$roman");
	ft_lexer(data);
	print_list(&data->list);
	ft_expand(data);
	exit(0);
}

/*Add - prompt, history, env linked list (env_lst)*/
//i think it does not free line at the end 
int main(int argc, char **argv, char **envp)
{
	// t_input		input;
	char	*line_buffer;
	t_minishell	data;
	// char	**after_split;
	initializer_data(&data);
	ft_env(&data, envp);
	(void) (argc);
	(void) (argv);
	while (1)
	{
		signals_main(&(data.termios_default));
		line_buffer = readline("minishell $ ");
		data.line = line_buffer; //what about free line_buffer??
		add_history(line_buffer); // is it &data.line ?? , 
		// after_split = ft_split_meta(line_buffer);
		// print_2d(after_split);
		ft_lexer(&data);
		// print_list(&data.list);
		ft_expand(&data);
		printf("\n*********Print after expand******\n\n");
		print_list(&data.list);
		//init_simulation(&data);
		//ft_execution(&data);
		

		delete_list(&data.list); //para que no queden leaks
		//ft_parser(&list, line_buffer);

		free(line_buffer);

		//atexit(check_leaks);
		//system("leaks minishell");
	}
	return (0);
}
