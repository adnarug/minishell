/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:00:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 20:23:15 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	write_to_hdoc(t_minishell *data, char *input,
			t_prs_tok *token, int fd)
{
	(void) data;
	input = ft_strjoin(input, "\n");
	if (write(fd, \
		input, ft_strlen(input)) < 0)
	{
		perror(token->word);
		exit(EXIT_FAILURE);
	}
}

/*Reading and writing hdcos to the specific files*/
static void	read_from_stdin(t_minishell *data, t_prs_tok *token, int fd)
{
	char	*input;
	bool	lim_found;

	signals_heredoc_process();
	lim_found = false;
	while (lim_found == false)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (token->word && input && ft_strcmp(input, token->word) == 0)
			lim_found = true;
		else
			write_to_hdoc(data, input, token, fd);
		free(input);
		input = NULL;
	}
	if (close(fd) < 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

/*Creating files for each hdoc with the filename
matching the index*/
static int	create_hdoc_files(t_minishell *data)
{
	int		i;
	char	*hdoc_index;

	i = 0;
	data->hdoc->fd_tmp = malloc(sizeof(int) * (data->hdoc->num_hdocs));
	if (data->hdoc->fd_tmp == NULL)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	while (i < data->hdoc->num_hdocs)
	{
		hdoc_index = ft_itoa(i);
		data->hdoc->fd_tmp[i] = open(hdoc_index, \
			O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->hdoc->fd_tmp[i] < 0 \
			|| access(hdoc_index, F_OK) < 0 || access(hdoc_index, R_OK) < 0)
			return (EXIT_FAILURE);
		free(hdoc_index);
		hdoc_index = NULL;
		if (close(data->hdoc->fd_tmp[i]) < 0)
		{
			g_glob_var_exit = 1;
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/*Launching a child process to read from STDIN for each hdoc*/
static void	read_to_hdoc(t_minishell *data, t_prs_tok *token)
{
	int		status;
	int		pid;
	char	*hdoc_index;
	int		fd;

	status = 0;
	hdoc_index = 0;
	pid = fork();
	if (pid < 0)
		perror(NULL);
	else if (pid == 0)
	{
		hdoc_index = ft_itoa(data->hdoc->index);
		fd = open(hdoc_index, O_RDWR, 0644);
		free(hdoc_index);
		read_from_stdin(data, token, fd);
	}
	waitpid(pid, &status, 0);
}

/*Count hdocs, creates a file in the same folder with the number
matching the index of the hdoc, stores its fd and pointer to the
node with the hdoc. */
int	resolve_hdocs(t_minishell	*data)
{
	int	i;

	i = 0;
	init_hdocs(data);
	count_hdocs(data);
	if (data->hdoc->num_hdocs == 0)
	{
		data->hdoc->is_hdoc = false;
		return (EXIT_SUCCESS);
	}
	else
		data->hdoc->is_hdoc = true;
	create_hdoc_files(data);
	find_hdoc_nodes(data);
	while (i < data->hdoc->num_hdocs)
	{
		read_to_hdoc(data, data->hdoc->hdocs_nodes[i]);
		data->hdoc->index++;
		i++;
	}
	reassign_hdoc_to_redir(data);
	return (EXIT_SUCCESS);
}
