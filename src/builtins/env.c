/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:12:57 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/20 13:57:58 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_env *env, char *argv) // Error handling is missing - permission denied, No such file or directory 
{
	t_env	*envp;
	
	envp = env; 
	(void)argv; //maybe needs a fix
	if (env == NULL)
		return (EXIT_FAILURE);
	print_env_lst(env);
	return (EXIT_SUCCESS);
}