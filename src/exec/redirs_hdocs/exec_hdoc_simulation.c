/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:00:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/29 16:51:10 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 0
#include "../../../include/minishell.h"

/*Reading and writing hdcos to the specific files*/
static void	read_from_stdin(t_minishell *data, t_prs_tok *token)
{
	char	*input;
	bool	lim_found;

	lim_found = false;
	while (lim_found == false)
	{
	//	ft_signals(HDOC);
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strcmp(input, token->word) == 0)
			lim_found = true;
		else
		{
			input = ft_strjoin(input, "\n");
			if (write(data->hdoc->fd_tmp[data->hdoc->index], input, ft_strlen(input)) < 0)
			{
				perror(token->word);
				exit(EXIT_FAILURE);
			}
		}
		free(input);
		input = NULL;
	}
	exit(EXIT_SUCCESS);
}

/*Creating files for each hdoc with the filename
matching the index*/
static int create_hdoc_files(t_minishell *data)
{
	int		i;
	char	*hdoc_index;
	int		fd;
	
	i = 0;
	data->hdoc->fd_tmp = malloc(sizeof(int) * (data->hdoc->num_hdocs));
	if (data->hdoc->fd_tmp == NULL)
		return(EXDEV);
	if (DEBUG == 1)
		printf("comes to open\n");
	while (i < data->hdoc->num_hdocs)
	{
		hdoc_index = ft_itoa(i);
		data->hdoc->fd_tmp[i] = open(hdoc_index, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->hdoc->fd_tmp[i]< 0 || access(hdoc_index, F_OK) < 0 || access(hdoc_index, R_OK) < 0)
			return (EXIT_FAILURE);
		free(hdoc_index);
		hdoc_index = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

/*Launching a child process to read from STDIN for each hdoc*/
static void read_to_hdoc(t_minishell *data, t_prs_tok *token)
{
	int	status;
	int pid;

	status = 0;
	pid = fork();
	if (pid < 0)
		perror(NULL);
	else if (pid == 0)
		read_from_stdin(data, token);
	waitpid(pid, &status, 0);
	/*
	if (WIFEXITED(status))
	{
		g_exit_code = WEXITSTATUS(status);
		if (g_exit_code == EXIT_FAILURE)
			data->parse_error = true;
	}*/
}

/*Finds all nodes of t_prs_tok with hdocs, creates
an array of hdocs in data->hdoc*/
static t_prs_tok	*find_hdoc_nodes(t_minishell *data)
{

	t_prs_tok		*tmp_prs_tk;
	int 			i;
	int				counter;

	i = 0;
	counter = 0;

	data->hdoc->hdocs_nodes = malloc(sizeof(t_prs_tok * ) * (data->hdoc->num_hdocs));
	if (data->hdoc->hdocs_nodes == NULL)
		return NULL;
	while(data->array_sublist[i] != NULL)
	{
		tmp_prs_tk= data->array_sublist[i]->prs_tok;
		while(tmp_prs_tk!= NULL)
		{
			if (tmp_prs_tk->type == HEREDOC)
			{
				data->hdoc->hdocs_nodes[i] = tmp_prs_tk;
				i++;
			}
			tmp_prs_tk = tmp_prs_tk->next;
		}
		counter++;
	}
	return (NULL);
}

void init_hdocs(t_minishell *data)
{
	data->hdoc = malloc(sizeof(t_hdocs));
	if (data->hdoc == NULL)
		return ;
	data->hdoc->num_hdocs = 0;
	data->hdoc->index = 0;
	data->hdoc->fd_tmp = NULL;
	data->hdoc->hdocs_nodes = NULL;
	data->hdoc->is_hdoc = false;
}

/*Count hdocs, creates a file in the same folder with the number
matching the index of the hdoc, stores its fd and pointer to the
node with the hdoc. */
int resolve_hdocs(t_minishell	*data)
{
	int	i;
	t_prs_tok	*hdoc_for_exec;

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

	if (DEBUG == 1)
		printf("num of heredocs %i\n", data->hdoc->num_hdocs);
	find_hdoc_nodes(data);
	while (i < data->hdoc->num_hdocs)
	{
		read_to_hdoc(data, data->hdoc->hdocs_nodes[i]);
		// destroy_hdocs(data);
		data->hdoc->index++;
		i++;
	}
	i = 0;
	/*Turning hdocs in redirs*/
	while (i < data->hdoc->num_hdocs)
	{
		data->hdoc->hdocs_nodes[i]->type = REDIRECT_IN;
		data->hdoc->hdocs_nodes[i]->word = ft_itoa(i);
		i++;
	}
	// free(data->hdoc->fd_tmp);
	// free(data->hdoc->hdocs_nodes);
	return (EXIT_SUCCESS);
}
