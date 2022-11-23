/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:37:58 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/22 12:32:20 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	open_files(char *infile_name, char *outfile_name, int *fd)
{
	fd[0] = open(infile_name, O_RDWR, 0777);
	fd[1] = open(outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd[0] == -1 || fd[1] == -1)
		error("Error\nCould not open the files - check filename/path", 1);
	return ;
}

void	open_file_std(int *fd)
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (fd[0] == -1 || fd[1] == -1)
		error("Error\nCould not open the files - check filename/path", 1);
	return ;
}
