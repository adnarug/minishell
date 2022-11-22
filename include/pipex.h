/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:52:02 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/22 12:32:32 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define INFILE 0
# define OUTFILE 1

typedef struct s_param
{
	pid_t			pid;
	char			**cmd1_flags;
	char			**cmd2_flags;
	char			*correct_path1;
	char			*correct_path2;
}	t_param;

void	print_2d(char **array);
void	sort_params(char **argv, t_param *parameters);
int		count_strings(char **array);
void	open_files(char *infile_name, char *outfile_name, int *fd);
void	init_params(t_param *parameters, char *cmd1_flags, char *cmd2_flags);
// int		find_correct_paths(t_param *parameters, char **envp);
void	error(char *message, int exit_code);
void	free_2d(char **array);
void	check_args_validity(int argc, char **argv);
char	**extract_cmd_flags(char *cmd_flags_input);
void	open_file_std(int *fd);

#endif