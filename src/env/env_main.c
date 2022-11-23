/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:47:08 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/22 12:04:12 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_minishell *data, char **envp)
{
	char		**dup_env;
	int			status;

	status = 0;
	dup_env = dup_env_matrix(envp);
	data->env_argv = dup_env;
	data->env_lst = create_env_lst(dup_env);
}