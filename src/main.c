/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/26 16:38:21 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Add - prompt, history, env linked list (env_lst)*/
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
		
		ft_parser(&list, line_buffer);
		// printf("till here ft_parser ok \n");
		// dup_env = dup_matrix(envp);
		// env_lst = ft_initializer(dup_env);
		// // print_env_lst(env_lst);
		// free(line_buffer);
		// ft_lst_free(env_lst);
		// ft_free_2d(dup_env);
		//system("leaks minishell");
	}
}
