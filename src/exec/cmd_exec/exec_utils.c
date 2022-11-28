/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:19:06 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 13:11:28 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


int	check_pipe_redir(char *c)
{
	if (c == PIPE)
		return (TYP_PIPE);
	if (c == HEREDOC)
		return (TYP_HEREDOC);
	if (c == APPEND)
		return (TYP_APPEND);
	if (c == REDIRECT_IN)
		return (TYP_REDIRECT_IN);
	if (c == REDIRECT_OUT)
		return (TYP_REDIRECT_OUT);
	return (0);
}

int make_command_table(char *argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i] != NULL)
	{
		while(check_pipe_redir(argv[i][j]) == 0)
			j++;
		i++;
	}
	if argv[1]
} 

// /*
// 	Extracts the cmd and path based on the following cases:
	
// 	1) Absolute or relative path is given:
// 		extracts the path from the given input.
// 		searches for the appropriate cmd in PATH env and saves it as exec->cmd.
	
// 	2) Only the command name is given:
// 		searches for the appropriate cmd in PATH env and saves it as cmd with
// 		another arguments (next word tokens).
// 		Then also adds the found path to exec->path.
// */
// static void	extract_cmd_and_path(t_data *data, t_token *token)
// {
// 	if (data->exec->no_cmd == true || !data->tokens->content)
// 		return ;
// 	if (token->content[0] == '.' || token->content[0] == SLASH)
// 	{
// 		data->exec->cmd = extract_cmd_from_path(data);
// 		if (!data->exec->cmd || !data->exec->path)
// 		{
// 			data->exec_error = true;
// 			return ;
// 		}
// 	}
// 	else
// 	{
// 		data->exec->cmd = get_cmd(data);
// 		if (data->exec_error == true)
// 			return ;
// 		data->exec->path = get_cmd_path(data);
// 		if (!data->exec->path)
// 			data->exec_error = true;
// 	}
// }

// /*
// 	Extracts the cmd and path and executes the given token (cmd).
// 	Redirects the cmd input/output based on the cmd number.
// */
// static void	exec_cmd(t_data *data, t_token *token)
// {
// 	extract_cmd_and_path(data, token);
// 	if (data->exec->cmd_num < data->exec->last_cmd)
// 		pipe_transitory_cmd(data);
// 	else if (data->exec->cmd_num == data->exec->last_cmd)
// 		pipe_last_cmd(data);
// 	free_cmd_and_path(data);
// }

// /* reset parameters to initial values. */
// static void	reset_params(t_data *data)
// {
// 	data->parse_error = false;
// 	data->exec_error = false;
// 	data->exec->no_cmd = false;
// 	data->fd->in = STDIN_FILENO;
// 	data->fd->out = STDOUT_FILENO;
// }


// void	init_exec(t_data *data)
// {
// 	data->exec->cmd = NULL;
// 	data->exec->path = NULL;
// 	data->exec->cmd_num = 1;
// 	data->exec->last_cmd = 0;
// 	data
// /*
// 	Algorithm for executing commands, separated with pipes.

// 	Given are at the beginning tokens with already merged 
// 	redirections.
// 	First the redirections are resolved. As a result we get
// 	the final input fd_in and output fd_out.
// 	After that a command is built from all word tokens until the pipe/end.
// 	The command is executed and redirected until the next pipe 
// 	over the desired input/output.
//  	All word tokens are immediately deleted after execution.
// 	At the end the allocated heredoc-files are deleted and freed.
// */
// void	execute_tokens(t_nod_token *node, t_minishell *data)
// {
// 	init_exec(data);
// 	data->exec->last_cmd = ft_get_num_cmds(data);
// 	data->fd->hdoc_index = 0;
// 	while (data->tokens != NULL)
// 	{
// 		reset_params(data);
// 		resolve_redirections(data);
// 		if (!data->tokens)
// 		{
// 			reset_stdin_stdout(data);
// 			set_global_exit_code(data);
// 		}
// 		else if (data->exec->no_cmd == true || data->tokens->flag == T_WORD)
// 		{
// 			exec_cmd(data, data->tokens);
// 			data->exec->cmd_num++;
// 		}
// 		delete_words(data);
// 		ft_del_first_token(&data);
// 		close_fds_in_out(data);
// 	}
// 	catch_exit_code(data);
// 	destroy_hdocs(data);
// }


// int sorted_token(t_minishell )
// <test2 grep hi >text1 |  wc -w >> text2
// 1. < test2 grep hi
// 	type
// 2. wc -w 