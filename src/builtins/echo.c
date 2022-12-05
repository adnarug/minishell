/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:18 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/05 11:41:59 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	builtin_echo(char **args_echo)//to be adjusted based on the token format
// {
// 	int	nl_flag;

// 	nl_flag = 1;
// 	if (ft_strncmp(*args_echo, "echo ", 4) != 0)
// 		return(EXIT_FAILURE);
// 	args_echo++;
// 	if (ft_strncmp(*args_echo, "-n", 2) == 0)
// 	{
// 		nl_flag = 0;
// 		args_echo++;
// 	}
// 	while (*args_echo != NULL)
// 	{
// 		printf("%s", *args_echo);
// 		args_echo++;
// 	}
// 	if (nl_flag == 1)
// 		printf("\n");
// 	return (EXIT_SUCCESS);
// }


// static int	check_exit_code_request(t_data *data)
// {
// 	char	**args;

// 	args = ft_split(data->tokens->content, SPACE);
// 	if (!args)
// 		return (EXIT_FAILURE);
// 	if (args[1] != NULL)
// 	{
// 		if (ft_strcmp(args[1], "$?") != 0)
// 			g_exit_code = EXIT_SUCCESS;
// 	}
// 	ft_cleansplit(args);
// 	args = NULL;
// 	return (g_exit_code);
// }


static int	is_flag(char **cmd_flags)
{
	int	i;

	i = 1;
	while (ft_strncmp(cmd_flags[i], "-n", 2) == 0)
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

int counter_2d(char **cmd_flags)
{
	int	i;

	i = 0;
	while (cmd_flags[i] != NULL)
		i++;
	return (i);
}
/*
echo without args will just print a new line
echo -n = without new line
echo text will print the text include a new line
*/
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
	// glob_var_exit = check_exit_code_request(data);
	return (0);
}
