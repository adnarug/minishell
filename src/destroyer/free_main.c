/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:03:09 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/03 18:31:39 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
	it wil.l have 4 parameters , 
	what to free
	error to print
	int global var
	needs to exit?
	Errors have to be inizialice to true in the begginig of each function (lex, parse, execut)
	data.exit_minishell , will be only set to false if we need to exit,
	otherwise we set the rest of errors to false , to prompt again
	
*/
// void print_error_free_exit(t_minishell *data, char *error_msg, int glb_var, bool do_exit)
// {
// 	write (2, error_msg, ft_strlen(error_msg));
// 	free_all(data);
// 	glob_var_exit = glb_var;
// 	if (do_exit)
// 		exit(glob_var_exit);
// 	data->lx_error = false;
// 	data->prs_error = false;
// 	//maybe also exe
// 	// if it does not exit 
// 	/*
	
// 	*/

	
// }



void	free_all(t_minishell *data)
{
	// close(data->curr_fd_in);
	// close(data->curr_fd_in);
	ft_lst_free(data->env_lst);
	ft_free_2d(data->env_argv);
	del_parsedtk_and_list_tok(data);
	// del_array_list_prsdtok(data);
	// delete_list(&data->list); 
	free(data->exec);
	close(data->std_in);
	close(data->std_out);
}
