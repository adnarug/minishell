/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:58:21 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/15 13:58:24 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
1. 2D array first element is echo, then what is to print
2. Possibly, second -n
3. If only echo, then empty line only. 
*/

int	builtin_echo(char **args_echo)
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

int	builtin_pwd(char *args_pwd)
{
	char	*path;

	path = getcwd(path, MAXPATHLEN);//instead of MATXPATHLEN rm put 0
	if (ft_strncmp(args_pwd, "pwd", 3) != 0)
		return(EXIT_FAILURE);
	else
		printf("%s", path);
	return(EXIT_SUCCESS);
}

// int	builtin_cd(char *args_cd)
// {
// 	char	**env;
	
// 	env = getenv(env);
// 	if( args_cd == NULL || env == NULL)
// 		return (EXIT_FAILURE);
// }