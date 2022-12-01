/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:03:09 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/01 13:28:49 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
	it wil.l have 4 parameters , 
	what to free
	error to print
	int global var
	needs to exit?
	
*/
void print_error_free_exit(t_minishell *data, char *error_msg, int glb_var, bool do_exit)
{
	write (2, error_msg, ft_strlen(error_msg));
	free_all(data);
	glob_var_exit = glb_var;
	if (do_exit)
		exit(glob_var_exit);
}


void free_all(t_minishell *data)
{
	delete_list(&data->list); 
	// and keep deleting
	//printf ("we free all from all");
}

