/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/20 20:17:05 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
 11/11/22
 Incluir en el nodo de la lista un char para el texto antiguo y para despues de la expansion
 Incluir en el nodo si hay comillas o no . Vermos despues
 echo $ $ >> no hay que expandir
 echo text"$USER" >>> Expandir sin tener en cuenta las "" , also for cd,  cd "$HOME"

 atencion: rl_replace_line("", 0);
 brew link --force readline
 export C_INCLUDE_PATH="$HOME/.brew/include:$C_INCLUDE_PATH"
export LIBRARY_PATH="$HOME/.brew/lib:$LIBRARY_PATH"
 https://42born2code.slack.com/archives/CMX2R5JSW/p1626886311496500?thread_ts=1626883699.496000&cid=CMX2R5JSW
 https://42born2code.slack.com/archives/CMX2R5JSW/p1627056716030100?thread_ts=1626883699.496000&cid=CMX2R5JSW
 

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
	char	**after_split;
	
	//t_list_token	list; //reeemplazada por data
	t_minishell		data;
	initializer_data(&data);
	ft_env(&data, envp);
	//debuggear(&data); solo si queremos debugear
	while (1)
	{
		signals_main(&(data.termios_default));
		data.line = NULL; //do we need it always? is already done at initializer_data(&data);
		line_buffer = readline("minishell $ ");
		data.line = line_buffer;
		add_history(line_buffer); // is it &data.line ??
		// after_split = ft_split_meta(line_buffer);
		// print_2d(after_split);
		ft_lexer(&data);
		print_list(&data.list);
		ft_expand(&data);
		printf("\n*********Print after expand******\n\n");
		print_list(&data.list);
		ft_execution(&data);
		//atexit(check_leaks);
		//system("leaks minishell");
		//printf("till here ft_lexer ok \n");
		// print_env_lst(data.env_lst);
		delete_list(&data.list); //para que no queden leaks
		//ft_parser(&list, line_buffer);
		// dup_env = dup_matrix(envp);
		// env_lst = ft_initializer(dup_env);
		// // print_env_lst(env_lst);
		free(line_buffer);
		// free(data.line);
		// data.line = NULL;
		// ft_lst_free(env_lst);
		// ft_free_2d(dup_env);
		//atexit(check_leaks);
		//system("leaks minishell");
	}
	return (0);
}
