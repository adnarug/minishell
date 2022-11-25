/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:00:46 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/25 14:26:08 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 1
#include "../../include/minishell.h"
/*
- Count hdocs
- Malloc fds for hdoc
- Parse hdocs
    - Create hodc files
    - Add path and index
    - Create files and the access
    - Read to hdoc in a child process
        - Read from stdin */

int is_heredoc(t_prs_tok *prs_tok)
{
	t_prs_tok	*tmp;
	int			num_hdoc;

	tmp = prs_tok;
	num_hdoc = 0;
	while (tmp != NULL)
	{
		if (tmp->type == '-')
			num_hdoc++;
		tmp = tmp->next;
	}
	return (num_hdoc);
}

static int	count_hdocs(t_minishell *data)
{
	t_header_prs_tok *tmp_prs_lst;

	tmp_prs_lst = data->lst_prs;
	while (tmp_prs_lst != NULL)
	{
		if (is_heredoc(data->lst_prs->prs_tok) != 0)
			data->hdoc.num_hdocs += is_heredoc(data->lst_prs->prs_tok);
		tmp_prs_lst = tmp_prs_lst->next;
	}
	return (EXIT_SUCCESS);
}

static void	read_from_stdin(t_minishell *data, t_prs_tok *token)
{
	char	*input;
	bool	lim_found;
	int		fd;

	lim_found = false;
	
	// if (fd < 0 || access("/tmp/tmo2", F_OK) < 0 || access("/tmp/tmo2", R_OK) < 0)
	// {
	// 	if (DEBUG == 1)
	// 		printf("problem with fd of hdoc\n");
	// 	perror(NULL);

	// }
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
			if (write(data->hdoc.fd_tmp[data->hdoc.index], input, ft_strlen(input)) < 0)
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

int create_hdoc_files(t_minishell *data)
{
	// char	**hdoc_files_table;
	char	*tmp;
	int		i;
	char	*hdoc_index;
	int		fd;
	
	i = 0;
	// tmp = ft_strdup("/tmp/");
	data->hdoc.fd_tmp = malloc(sizeof(int) * (data->hdoc.num_hdocs + 1));
	if (data->hdoc.fd_tmp == NULL)
		return(EXDEV);
	if (DEBUG == 1)
		printf("comes to open\n");
	while (i < data->hdoc.num_hdocs)
	{
		hdoc_index = ft_itoa(i);
		// hdoc_files_table[i] = malloc(sizeof(char) * ft_strlen(hdoc_index));//maybe +1
		// if (hdoc_files_table[i] == NULL)
		// 	return (NULL);
		data->hdoc.fd_tmp[i] = open(hdoc_index, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->hdoc.fd_tmp[i]< 0 || access(hdoc_index, F_OK) < 0 || access(hdoc_index, R_OK) < 0)
			return (EXIT_FAILURE);
		free(hdoc_index);
		hdoc_index = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

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

static void	destroy_hdocs(t_minishell *data)
{
	int	i;

	if (data->hdoc.fd_tmp == NULL)
		return ;
	i = 0;
	unlink(ft_itoa(data->hdoc.index));
	// free(data->hdoc.fd_tmp);
}

t_prs_tok	*return_heredoc(t_prs_tok *prs_tok)
{
	t_prs_tok	*tmp;
	int			num_hdoc;

	tmp = prs_tok;
	num_hdoc = 0;
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_prs_tok	*iter_till_hdoc(t_minishell *data)
{
	t_header_prs_tok *tmp_prs_lst;
	int	i;

	tmp_prs_lst = data->lst_prs;
	i = 0;
	data->hdoc.hdocs_nodes = malloc(sizeof(t_prs_tok) * (data->hdoc.num_hdocs));
	if (data->hdoc.hdocs_nodes == NULL)
		return NULL;
	while (tmp_prs_lst != NULL)
	{
		while (tmp_prs_lst->prs_tok != NULL)
		{
			if (tmp_prs_lst->prs_tok->type == HEREDOC)
			{
				data->hdoc.hdocs_nodes[i] = *(tmp_prs_lst->prs_tok);
				i++;
			}
			tmp_prs_lst->prs_tok = tmp_prs_lst->prs_tok->next;
		}
		tmp_prs_lst = tmp_prs_lst->next;
	}
	return (NULL);
}

/*Counts hdocs, if >0 continues, creates hdoc files and fds*/
int resolve_hdocs(t_minishell	*data)
{
	int	i;
	t_prs_tok	*hdoc_for_exec;

	i = 0;
	data->hdoc.num_hdocs = 0;
	data->hdoc.index = 0;
	count_hdocs(data);
	if (data->hdoc.num_hdocs == 0)
		data->hdoc.is_hdoc = false;
	create_hdoc_files(data);
	if (DEBUG == 1)
		printf("num of heredocs %i\n", data->hdoc.num_hdocs);
	iter_till_hdoc(data);
	while (i < data->hdoc.num_hdocs)
	{
		read_to_hdoc(data, &data->hdoc.hdocs_nodes[i]);
		destroy_hdocs(data);
		data->hdoc.index++;
		i++;
	}
	return (EXIT_SUCCESS);
}
