/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:51:50 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/25 14:35:36 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_isnumber(char *s)
{
	int	i;

	i = 0;
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
int	check_exit_args(int *arg_equal_one, char **token)
{
	int	i;
	int	counter;

	printf("case0\n");
	i = count_strings(token);
	printf("i=%d\n", i);
	counter = 1;
	// printf("%d",i);
	if (i > 1)
	{
		if (ft_isnumber(token[counter]) == 1 && i == 2)
		{
			printf("immediate return");
			return (ft_atol(token[counter]) % 256);
		}
		else if (ft_isnumber(token[counter]) == 1 && i > 2)
		{
			printf("case1");
			*arg_equal_one = 0;
			// print_error(EXIT_ERROR); TODO: correct exit
			return (EXIT_FAILURE);
		}
		else if (ft_isnumber(token[counter]) == 0)
		{
			printf("case2");
			// Correct exit
			// exec_error(EXIT_ARG_ERROR, data->exec->cmd[1]);
			// return (INVALID_EXIT_ARG);
			return (EXIT_FAILURE);
		}
		printf("case3");
	}
	return (EXIT_SUCCESS);
}
/*
exit minishell
*/
int	builtin_exit(char **token)
{
	int		flag_exit_noargs;
	int		return_code;

	flag_exit_noargs = 1;
	return_code = check_exit_args(&flag_exit_noargs, token);
	if (flag_exit_noargs == 1)
		write(2, "exit\n", 5);
	exit(return_code);
	return (return_code);
}
