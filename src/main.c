/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/31 01:23:52 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//hay que inicializar la lista () con malloc??

void	initializer_data(t_minishell *data)
{
	data->line = NULL;
	data->list = NULL;
	// data->list->head = list->head;
	// data->list->size = 0;
	//init_list_tok(&data->list);
}

/*
	atexit(check_leaks);
*/
void	check_leaks(void)
{
	system("leaks minishell");
}


/*Add - prompt, history, env linked list (env_lst)*/
//i think it does not free line at the end 
int main(int argc, char **argv, char **envp)
{
	// t_input		input;
	//char *line_buffer; rremplazada por data
	t_env *env_lst;
	char **dup_env;
	char	**after_split;
	
	//t_list_token	list; //reeemplazada por data
	t_minishell		data;
	t_list_token list;

	initializer_data(&data);

	while (1)
	{
		data.line = NULL; //do we need it always?

		data.line = readline("minishell $ ");
		add_history(data.line); // is it &data.line ??
		// after_split = ft_split_meta(line_buffer);
		// print_2d(after_split);
		ft_lexer(&data);
		//atexit(check_leaks);

		//system("leaks minishell");

		//printf("till here ft_lexer ok \n");
		print_list(data.list);
		delete_list(data.list); //para que no queden leaks
		//ft_parser(&list, line_buffer);
		// dup_env = dup_matrix(envp);
		// env_lst = ft_initializer(dup_env);
		// // print_env_lst(env_lst);
		free(data.line);
		// ft_lst_free(env_lst);
		// ft_free_2d(dup_env);
		//atexit(check_leaks);
		//system("leaks minishell");
	}
	//system("leaks minishell");
	return (0);
}
