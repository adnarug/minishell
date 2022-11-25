/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:45:57 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/25 20:15:24 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H


//this structur will be in the case we need to increase the number of paramters
typedef struct s_lexing
{
	char	*buff;
	int		c_pos;
	char	c; //we can take out
	char	type;
	int		simple_quote;
	int		double_quote;
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
	char			type;
	char			*word;
	char			**cmd_flags;

	struct s_prs_tok *next;
}	t_prs_tok; 

/*
    List of headers to sublist of parsed tokens between pipes
    t_prs_tok	*first_prs_tok; : First element from list of parsed tokens
    struct s_sublist_prs_tok *next_sublist: first element of list form list
*/

typedef struct s_sublist_prs_tok
{
	t_prs_tok					*first_prs_tok;
	char						*exec_path;
	int							fd_in; //nomally 0 (STDIN)
	int							fd_out; //nomrally 1 (STDOUT)
	int							size_sublist;
	struct s_sublist_prs_tok		*next_sublist;
}	t_sublist_prs_tok;

typedef struct t_head_sublst_parstk
{
	int		number_sublists;
	t_sublist_prs_tok 	*first_sublist;
} t_head_sublst_parstk;

typedef struct s_minishell
{
	char				*line;
	t_env				*env_lst;
	char				**env_argv;
	t_list_token		list; //
	t_head_sublst_parstk	lst_sublist; //header a headers de sublistas (lista de sublistas)
	struct termios		termios_default;
}t_minishell;


#endif

