/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:49:08 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/22 12:37:45 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	parent_process(t_param parameters, int *fd,
	int *pipe_end, char **envp)
{
	int	status;

	status = 0;
	if ((ft_strncmp(parameters.cmd1_flags[0], "sleep", 5) == 0)
		|| (ft_strncmp(parameters.cmd1_flags[0], "usleep", 6) == 0))
		waitpid(0, NULL, 0);
	else
		waitpid(0, &status, WNOHANG);
	dup2(fd[OUTFILE], STDOUT_FILENO);
	dup2(pipe_end[0], STDIN_FILENO);
	close(pipe_end[1]);
	close(fd[OUTFILE]);
	if (execve(parameters.correct_path2, parameters.cmd2_flags, envp) == -1)
		error("Error\nExecve issue in the parent", 1);
}

static void	child_process(t_param parameters, int *fd,
	int *pipe_end, char **envp)
{
	dup2(fd[INFILE], STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	close(fd[INFILE]);
	if (execve(parameters.correct_path1, parameters.cmd1_flags, envp) == -1)
		error("Error\nExecve issue in the child", 1);
}

char	**extract_cmd_flags(char *cmd_flags_input)
{
	char	**cmd_flags_output;
	int		line_count;
	int		i;

	i = 0;
	cmd_flags_output = ft_split(cmd_flags_input, ' ');
	line_count = count_strings(cmd_flags_output);
	while (i < line_count)
	{
		if (cmd_flags_output[i] == NULL || *cmd_flags_output[i] == ' ')
			error("Error\nCheck the cmd and flags", 127);
		i++;
	}
	return (cmd_flags_output);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_param	parameters;
	int		fd[2];
	int		pipe_end[2];

	if (envp == NULL)
		error("Error\nCould not access env", 2);
	check_args_validity(argc, argv);
	printf("num of argc %i\n", argc);
	if (argc == 5)
		init_params(&parameters, argv[2], argv[3]);
	if (argc == 2)
		init_params(&parameters, argv[1], argv[2]);
	find_correct_paths(&parameters, envp);
	if (argc == 5)
		open_files(argv[1], argv[4], fd);
	if (argc == 2)
		open_file_std(fd);
	if (pipe(pipe_end) == -1)
		error("Error\nCould not open the pipe", 1);
	parameters.pid = fork();
	if (parameters.pid == -1)
		error("Error\nCould not fork", 1);
	if (parameters.pid == 0)
		child_process(parameters, fd, pipe_end, envp);
	if (parameters.pid != 0)
		parent_process(parameters, fd, pipe_end, envp);
	return (0);
}
