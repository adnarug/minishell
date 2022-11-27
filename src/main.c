/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/27 14:40:42 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
	tcgetattr(STDOUT_FILENO, &data->termios_default);
	We make a copy of the default atributes of termios
*/

//void initializer_header_sublist(t_minishell *data)

void	initializer_data(t_minishell *data) //still any values to inicialze (could be done in the later functions but all variables must be inizialice)
{
	data->line = NULL;
	data->list.head = NULL;
	data->list.size = 0;
	
	//initializer_header_sublist(data);
	data->array_sublist = NULL;
	data->number_pipes = 0;
	// ask PAvel about the other all his var to inizialice
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
		//printf("\n*********Print after expand******\n\n");
		//print_list(&data.list);
		ft_parser(&data);
		//init_simulation(&data);
		//ft_execution(&data);
		print_list_parsedtoken(&data);
		delete_list(&data.list); //free before here. No needed
		free(line_buffer);//free before here. No needed
		printf("here ends minishell\n");
		//atexit(check_leaks);
		//system("leaks minishell");
	}
	return (0);
}
