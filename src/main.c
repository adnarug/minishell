/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/15 13:44:08 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 11/11/22
 Incluir en el nodo de la lista un char para el texto antiguo y para despues de la expansion
 Incluir en el nodo si hay comillas o no . Vermos despues
 echo $ $ >> no hay que expandir
 echo text"$USER" >>> Expandir sin tener en cuenta las "" , also for cd,  cd "$HOME"

 Emezar con las senales
*/


void	initializer_data(t_minishell *data)
{
	t_list_token list; //repetimos el proceso que en la funcion previa
	
	
	data->line = NULL;
	data->list = list;
	data->list.head = NULL;
	data->list.size = 0;
	//init_list_tok(data->list);
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
		signals_execut(MAIN);
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
		//ft_execution(&data);
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
