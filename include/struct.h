/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:45:57 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/30 18:27:04 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <stdbool.h>


//this structur will be in the case we need to increase the number of paramters
typedef struct s_lexing
{
	char	*buff;
	int		c_pos;
	// char	c; //we can take out
	char	type;
	// int		simple_quote;
	// int		double_quote;
	int		expand;
	char	quote;
	//char	*ptr;
}t_lexing;



typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env *next;
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
	char	*name;
	char	flag;//can we rename flag into type?
	int		simple_quote;
	int		double_quote;
	char	quote;
	char	*exec_path;
	char	**argv;

	struct s_nod_token	*next;
	
}	t_nod_token;

//struct header of the token list
typedef struct s_list_token
{
	t_nod_token	*head;
	int	size;
}	t_list_token;

//main structur. Here will pend everything but lexing struct
typedef struct s_prs_tok
{
	char            type;
	char            *word;
	char            **cmd_flags;

	struct s_prs_tok *next;
}   t_prs_tok;
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
	t_prs_tok					*prs_tok;//CHANGED!
	char						*exec_path;
	int							fd_in; //nomally 0 (STDIN)
	int							fd_out; //nomrally 1 (STDOUT)
	int							size_sublist; //i do not think is important
	int							number_cmd; //if not 1 , error (we can just  one command per sublist)
	//struct s_sublist_prs_tok		*next_sublist; //not needed with the array
}	t_sublist_prs_tok;


typedef struct s_minishell
{
	char				*line;
	t_env				*env_lst;
	char				**env_argv;
	t_list_token		list; //
	struct termios		termios_default;
	t_sublist_prs_tok	**array_sublist; //array of sublists , ended in NULL with len + number of pipes + 2
	int 				number_pipes;
	
	t_hdocs				*hdoc;
	int					pipe[2];
	t_exec				*exec;
	pid_t				pid;
	bool				prs_error;
	bool				lx_error;
	bool				ex_error;
	bool				exit_minishell;
	int					curr_fd_in;
	int					curr_fd_out;
	int					std_in;
	int					std_out;
}	t_minishell;

// typedef struct t_head_sublst_parstk
// {
// 	int		number_sublists;
// 	t_sublist_prs_tok 	*first_sublist;
// } t_head_sublst_parstk;

#endif

