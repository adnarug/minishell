/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:58:21 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/26 16:30:55 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_pwd(char *args_pwd)//to be adjusted based on the token format
{
	char	*path;

	path = NULL;
	path = getcwd(path, MAXPATHLEN);
	if (ft_strncmp(args_pwd, "pwd", 3) != 0)
		return(EXIT_FAILURE);
	else
		printf("%s\n", path);
	free(path);
	path = NULL;
	return(EXIT_SUCCESS);
}