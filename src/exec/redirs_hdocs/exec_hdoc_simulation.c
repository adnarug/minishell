/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:00:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 21:54:15 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 1
#include "../../../include/minishell.h"

/*Reading and writing hdcos to the specific files*/
static void	read_from_stdin(t_minishell *data, t_prs_tok *token)
{
	char	*input;
	bool	lim_found;
	int		fd;

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
	char	*tmp;
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
static void	read_to_hdoc(t_minishell *data, t_prs_tok *token)
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
	t_header_prs_tok *tmp_prs_lst;
	int	i;

	tmp_prs_lst = data->lst_prs;
	i = 0;
	data->hdoc->hdocs_nodes = malloc(sizeof(t_prs_tok) * (data->hdoc->num_hdocs));
	if (data->hdoc->hdocs_nodes == NULL)
		return NULL;
	while (tmp_prs_lst != NULL)
	{
		while (tmp_prs_lst->prs_tok != NULL)
		{
			if (tmp_prs_lst->prs_tok->type == HEREDOC)
			{
				data->hdoc->hdocs_nodes[i] = *(tmp_prs_lst->prs_tok);
				i++;
			}
			tmp_prs_lst->prs_tok = tmp_prs_lst->prs_tok->next;
		}
		tmp_prs_lst = tmp_prs_lst->next;
	}
	return (NULL);
}

/*Count hdocs, creates a file in the same folder with the number
matching the index of the hdoc, stores its fd and pointer to the
node with the hdoc. */
int resolve_hdocs(t_minishell	*data)
{
	int	i;
	t_prs_tok	*hdoc_for_exec;

	i = 0;
	data->hdoc = malloc(sizeof(t_hdocs));
	if (data->hdoc == NULL)
		return (NULL);
	data->hdoc->num_hdocs = 0;
	data->hdoc->index = 0;
	printf("hdocs here\n");
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
		read_to_hdoc(data, &data->hdoc->hdocs_nodes[i]);
		// destroy_hdocs(data);
		data->hdoc->index++;
		i++;
	}
	i = 0;
	while (i < data->hdoc->num_hdocs)
	{
		data->hdoc->hdocs_nodes[i].type = REDIRECT_IN;
		i++;
	}

	// free(data->hdoc->fd_tmp);
	// free(data->hdoc->hdocs_nodes);
	return (EXIT_SUCCESS);
}


void print_exec_lists(t_minishell *data)
{
	int i = 0;
	t_header_prs_tok *tmp;
	tmp = data->lst_prs;
	while(tmp != NULL)
	{
		while(tmp->prs_tok != NULL)
		{
			printf("type:%c ", tmp->prs_tok->type, i);
			if (tmp->prs_tok->type != COMMAND)
				printf("word:%s\n", tmp->prs_tok->word);
			if (tmp->prs_tok->type == COMMAND)
				printf("cmd:%s\n", tmp->prs_tok->cmd_flags[0]);
			i++;
			tmp->prs_tok = tmp->prs_tok->next;
		}
		printf("*****END OF A SUBLIST******\n");
		tmp = tmp->next;
	}
}