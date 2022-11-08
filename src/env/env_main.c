/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:47:08 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/08 11:04:44 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_minishell *data, char **envp)
{
	t_env		*env_lst;
	char		**dup_env;
	int			status;

	
	status = 0;
	dup_env = dup_env_matrix(envp);
	data->env_lst = create_env_lst(dup_env);
}