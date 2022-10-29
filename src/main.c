/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/29 20:31:08 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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
	char *line_buffer;
	t_env *env_lst;
	char **dup_env;
	char	**after_split;
	
	t_list_token	list;

	while (1)
	{
		line_buffer = NULL;

		line_buffer = readline("minishell $ ");
		add_history(line_buffer);
		// after_split = ft_split_meta(line_buffer);
		// print_2d(after_split);
		ft_lexer(&list, line_buffer);
		//atexit(check_leaks);

		//system("leaks minishell");

		//printf("till here ft_lexer ok \n");
		print_list(&list);
		delete_list(&list); //para que no queden leaks
		//ft_parser(&list, line_buffer);
		// dup_env = dup_matrix(envp);
		// env_lst = ft_initializer(dup_env);
		// // print_env_lst(env_lst);
		free(line_buffer);
		// ft_lst_free(env_lst);
		// ft_free_2d(dup_env);
		//atexit(check_leaks);
		//system("leaks minishell");
	}
	return (0);
}
