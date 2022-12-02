/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:58:21 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/29 15:45:17 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_pwd(char *args_pwd)
{
	char	*path;

	path = NULL;
	path = getcwd(path, MAXPATHLEN);
	if (path == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(args_pwd, "pwd", 3) != 0)
		return(EXIT_FAILURE);
	else
		printf("%s\n", path);
	free(path);
	path = NULL;
	return(EXIT_SUCCESS);
}