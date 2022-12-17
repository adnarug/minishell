/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:45:57 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/12 21:38:00 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdbool.h>

typedef struct s_lexing
{
	char	*buff;
	int		c_pos;
	char	type;
}	t_lexing;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*equal;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd_exec
{
	char	*cmd;
	char	*args;
	char	**cmd_args;
	char	*exec_path;
	int		cmd_num;
	int		last_cmd;
}	t_cmd_exec;

typedef struct s_nod_token
{
	char				*name;
	char				flag;
	int					simple_quote;
	int					double_quote;
	char				quote;
	char				*exec_path;
	char				**argv;
	struct s_nod_token	*next;
}	t_nod_token;

//struct header of the token list
typedef struct s_list_token
{
	t_nod_token	*head;
	int			size;
}	t_list_token;

//main structur. Here will pend everything but lexing struct
typedef struct s_prs_tok
{
	char				type;
	char				*word;
	char				**cmd_flags;
	struct s_prs_tok	*next;
}	t_prs_tok;

/*
	List of headers to parsed tokens between pipes	
	t_prs_tok   *tokens : Starting from list of tokens
	struct s_header_prs_tok *next: first element of list form list
*/
typedef struct s_exec
{
	char	**cmd_flags;
	char	*exec_path;
	int		cmd_num;
	int		last_cmd;
	bool	is_builtin;
	bool	is_executable;
	bool	no_cmd;
}		t_exec;

typedef struct s_hdocs
{
	bool			is_hdoc;
	int				index;
	int				*fd_tmp;
	t_prs_tok		**hdocs_nodes;
	int				num_hdocs;
}	t_hdocs;

/*
	List of headers to parsed tokens between pipes	
	t_prs_tok   *tokens : Starting from list of tokens
	struct s_header_prs_tok *next: first element of list form list
*/
typedef struct s_sublist_prs_tok
{
	t_prs_tok					*prs_tok;
	char						*exec_path;
	int							fd_in;
	int							fd_out;
	int							size_sublist;
	int							number_cmd;
}	t_sublist_prs_tok;

/*
	lx_error, and errors in general will be false 
	if there is an error. True , everything ok.
*/
typedef struct s_minishell
{
	char				*line;
	t_env				*env_lst;
	char				**env_argv;
	t_list_token		list;
	struct termios		termios_default;
	t_sublist_prs_tok	**array_sublist;
	int					number_pipes;
	t_hdocs				*hdoc;
	int					pipe[2];
	t_exec				*exec;
	pid_t				pid;
	bool				prs_error;
	bool				lx_error;
	bool				ex_error;
	bool				input_error;
	bool				exit_minishell;
	int					curr_fd_in;
	int					curr_fd_out;
	int					std_in;
	int					std_out;
	int					last_pid;
}	t_minishell;

#endif
