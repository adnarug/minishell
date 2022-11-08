/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:18 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/18 17:12:12 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_echo(char **args_echo)//to be adjusted based on the token format
{
	int	nl_flag;

	nl_flag = 1;
	if (ft_strncmp(*args_echo, "echo ", 5) != 0)
		return(EXIT_FAILURE);
	args_echo++;
	if (ft_strncmp(*args_echo, "-n", 2) == 0)
	{
		nl_flag = 0;
		args_echo++;
	}
	while (*args_echo != NULL)
	{
		printf("%s", *args_echo);
		args_echo++;
	}
	if (nl_flag == 1)
		printf("\n");
	return (EXIT_SUCCESS);
}
