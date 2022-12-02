/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:35:53 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/02 12:29:23 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_error_free_exit(t_minishell *data, char *error_msg, int glb_var, bool do_exit)
{
	write (2, error_msg, ft_strlen(error_msg));
	free_all(data);
	glob_var_exit = glb_var;
	if (do_exit)
		exit(glob_var_exit);
}

void exec_exit(t_minishell *data, char *error_msg, int glb_var, bool do_exit)
{
	write (2, error_msg, ft_strlen(error_msg));
	if (data->exec != NULL)
	{
		free(data->exec);
		data->exec = NULL;
	}
	if (data->hdoc != NULL)
	{
		free(data->hdoc);
		data->hdoc = NULL;
	}
	glob_var_exit = glb_var;
	if (do_exit)
		exit(glob_var_exit);
}