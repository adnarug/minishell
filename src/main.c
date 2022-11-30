/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/01 00:32:48 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
	Merge with Pasha. 
	change file strsuct. make everything work together,
	and after change the main.c, according to Rom model 

	este caso "'$USER'" >> atencion .echo text"'$USER'" ' $USER '  
	Real bash 'fnieves-'
	My bash fnieves- >>> se come las comillas simples
	ls -a | grep out | wc -l
	For wednesady:
	change main.c
	start to execute  easy errors , and problems with parsing , tokens,..

	question: if we have malloc problems , how do we indicate?
	
*/

//void initializer_header_sublist(t_minishell *data)

void	initializer_data_error(t_minishell *data) //still any values to inicialze (could be done in the later functions but all variables must be inizialice)
{
	data->prs_error = true;
	data->lx_error = true;
	data->ex_error = true;
	data->exit_minishell = true;
}


void	initializer_data(t_minishell *data) //still any values to inicialze (could be done in the later functions but all variables must be inizialice)
{
	glob_var_exit = 0;
	data->line = NULL;
	data->list.head = NULL;
	data->list.size = 0;
	data->array_sublist = NULL;
	data->number_pipes = 0;
	initializer_data_error(data);
	
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

/*
	Si el prompt nos da un NULL (equivalente a EOF),
	imprimimos exit y liberamos todo.
	En el caso de que sea string vacio, no lo guardamos en 
	el hitorial pero volvemos a mostrar el prompt
*/
void	data_input(t_minishell *data)
{
	data->line = readline("minishell $ ");
	if (data->line == NULL)
	{
		printf("exit\n"); //atention :its printing ^D: need to be deleted
		free_all(data);
		exit(glob_var_exit);
	}
	if (ft_strcmp(data->line, "")) //if its not equal to empty string
	{
		add_history(data->line);
	}
	ft_lexer(data);
	ft_expand(data); //put together with lexing
}

/*Add - prompt, history, env linked list (env_lst)*/


int main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	initializer_data(&data);
	ft_env(&data, envp); //could we add to inizialice
	while (data.exit_minishell)
	{
		signals_main(&(data.termios_default));
		data_input(&data);
		printf("\n*********Print after expand******\n\n");
		print_list(&data.list);
		if (data.lx_error)
		{
			ft_parser(&data);
			print_list_parsedtoken(&data);
			// if (data.prs_error)
			// 	//execute_tokens(&data);
		}
		//free tokens and parsed tokens
	}
	free_all(&data);
	return (glob_var_exit);
}


void free_all(t_minishell *data)
{
	delete_list(&data->list); 
	// and keep deleting
	//printf ("we free all from all");
}