/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/03 18:15:01 by pguranda         ###   ########.fr       */
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
	//printf("prompt again from main\n");
	data->line = readline("minishell $ ");
	if (data->line == NULL)
	{
		print_error_free_exit(data, ERROR_PRINTED, 1, true);
		// write(2, ERROR_PRINTED, ft_strlen(ERROR_PRINTED)); //is it ok?
		// data->exit_minishell = false;
		// data->lx_error = false;
		// //free_all(data);
		// exit(glob_var_exit);
	}
	if (ft_strcmp(data->line, "")) //if its not equal to empty string
		add_history(data->line);
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
	initializer_data(&data); //do we need to inizialez all here??
	ft_env(&data, envp); //could we add to inizialice
	while (data.exit_minishell)
	{
		signals_main(&(data.termios_default));
		data_input(&data);
		ft_lexer(&data);
		ft_expand(&data); //should not give any error beside memmry alloc
		// print_list(&data.list);//delete later
		//print_list(&data.list);//delete later
		//atexit(check_leaks);
		if (data.lx_error)
		{
			ft_parser(&data);
			//print_list_parsedtoken(&data);
			//print_list(&data.list);//delete later
			if (data.prs_error)
				ft_execution(&data);
		}
		del_parsedtk_and_list_tok(&data);
		//print_list_parsedtoken(&data);
		//print_list(&data.list);//delete later
		//Just free parser function, which also will free tokens//
	}

	free_all(&data);
	clear_history();
	system("leaks minishell");
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