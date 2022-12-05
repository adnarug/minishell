/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:51:50 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/05 14:00:44 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_isnumber(char *s)
{
	int	i;

	i = 0;
	if (s[i] =='+' || s[i] == '-')
		i++;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}
//Check if there are two elements or one 
int	check_exit_args(t_minishell *data, char **token)
{
	int	counter;
	int	len;
	int	exit_code;
	bool	error;


	counter = 1;
	error = false;
	len = counter_2d(token);
	if (len > 1)
	{
		if (ft_isnumber(token[counter]) == 1 && len == 2)
		{
			exit_code = ft_atol(token[counter], &error) % 256;
			if (error == true)
				my_strerror(token[counter], EXIT_NUM_ARG);
			data->exit_minishell = true;
			return (exit_code);
		}
		else if (ft_isnumber(token[counter]) == 0)
		{
			write(2, "exit\n", 5);
			my_strerror(token[counter], EXIT_NUM_ARG);
			data->exit_minishell = true;
			return (INVALID_EXIT_ARG);
		}
		else if (len > 2)
		{
			write(2, "exit\n", 5);
			cmd_str_error("exit", ": too many arguments\n");

			return (INVALID_ARG);
		}			
	}
	data->exit_minishell = true;
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_minishell *data)
{
	int		return_code;
	int		len;

	return_code = 0;

	return_code = check_exit_args(data, data->exec->cmd_flags);
	if (return_code != INVALID_ARG && return_code != INVALID_EXIT_ARG)
		write(2, "exit\n", 5);
	return(return_code);
}
