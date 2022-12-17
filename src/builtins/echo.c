/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:18 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 23:15:54 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_flag(char **cmd_flags)
{
	int	i;

	i = 1;
	while (cmd_flags[i] != NULL && ft_strncmp(cmd_flags[i], "-n", 2) == 0)
		i++;
	if (i != 1)
		return (i - 1);
	else
		return (0);
}

void	print_args(t_minishell *data, int len)
{
	char	**cmd_flags;
	int		flag;
	bool	check_flag;
	int		counter;

	flag = 0;
	check_flag = false;
	cmd_flags = data->exec->cmd_flags;
	counter = 1 + is_flag(cmd_flags);
	if (counter != 1)
		flag = 1;
	while (counter < len)
	{
		printf("%s", cmd_flags[counter]);
		if (counter < len - 1)
			printf(" ");
		counter++;
	}
	if (flag == 0)
		printf("\n");
}

int	counter_2d(char **cmd_flags)
{
	int	i;

	i = 0;
	while (cmd_flags[i] != NULL)
		i++;
	return (i);
}

int	builtin_echo(t_minishell *data)
{
	int	len;

	len = 0;
	len = counter_2d(data->exec->cmd_flags);
	if (len == 1)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	print_args(data, len);
	return (0);
}
