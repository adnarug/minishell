/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/01 17:53:28 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*

	In malloquing , if an error , exit and free with global erorr = 1
	update all the error en lexing, and checqu all the malloc will be free , properly
	Create the parser free, list
	question: if we have malloc problems , how do we indicate?

grep hi -l >> '$USER' | wc -w > $HOME | echo >> $? | cd "$USER" '"'$USER'"' "'$USER'" $$  << $

*/

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
		write(2, ERROR_PRINTED, ft_strlen(ERROR_PRINTED)); //is it ok?
		data->exit_minishell = false;
		data->lx_error = false;
		//free_all(data);
		exit(glob_var_exit);
	}
	if (ft_strcmp(data->line, "")) //if its not equal to empty string
		add_history(data->line);
	ft_lexer(data);
	ft_expand(data); //put together with lexing
	printf("\n*********Print after expand******\n\n");//delete later
	print_list(&data->list);//delete later
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
		if (data.lx_error)
		{
			ft_parser(&data);
			print_list_parsedtoken(&data);
			// if (data.prs_error)
			// 	//execute_tokens(&data);
		}
		//Just free parser function, which also will free tokens//
	}
	free_all(&data);
	return (glob_var_exit);
}


// void debuggear(t_minishell *data)
// // {
// // 	data->line = ft_strdup("$roman");
// // 	ft_lexer(data);
// // 	print_list(&data->list);
// // 	ft_expand(data);
// // 	exit(0);
// // }


/*
	atexit(check_leaks);
*/
void	check_leaks(void)
{
	system("leaks minishell");
}