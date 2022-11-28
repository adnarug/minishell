/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:45:57 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/28 11:32:34 by pguranda         ###   ########.fr       */
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
	char	c; //we can take out
	char	type;
	int		simple_quote;
	int		double_quote;
	int		expand;
	char	quote;
	//char	*ptr;
}t_lexing;


typedef struct s_cmd
{
	char	*name;
}t_cmd;

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

//main structur. Here will pend everything but lexing struct
typedef struct s_prs_tok
{
	char            type;
	char            *word;
	char            **cmd_flags;
	char			*exec_path;
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
	t_prs_tok		*hdocs_nodes;
	int				num_hdocs;
}	t_hdocs;

typedef struct s_header_prs_tok
{
	t_prs_tok                   *prs_tok;
	struct s_header_prs_tok     *next;
	char                        *exec_path;
	int                         fd_in;
	int                         fd_out;
	int                         size;
}	t_header_prs_tok;

typedef struct s_minishell
{
	char				*line;
	t_env				*env_lst;
	char				**env_argv;
	t_list_token		list; //esto hayq eu cambialo a un puntero. Volver a estudiar esto  y diferencia enntre pointer y &
	t_header_prs_tok	*lst_prs;
	t_hdocs				hdoc;
	int					pipe[2];//Parara
	t_exec				*exec; //Parara
	pid_t				pid; // Pararara
	bool				prs_error;
	bool				lx_error;
	bool				ex_error;
	int					curr_fd_in;
	int					curr_fd_out;
	int					std_in;
	int					std_out;
	struct termios		termios_default;
}	t_minishell;


// //--------- Estas funciones las he sacdo de una hoja. Borarr
// // Command Data Structure
// // Describes a simple command and arguments

//  struct SimpleCommand {
// 	// Available space for arguments currently preallocated 
// 	int _numberOfAvailableArguments;
// 	// Number of arguments
// 	int _numberOfArguments;
// 	// Array of arguments
// 	char ** _arguments;
// 	SimpleCommand();
// 	void insertArgument( char * argument );
//  };

// // Describes a complete command with the multiple pipes if any // and input/output redirection if any.
// struct Command {

// 	int _numberOfAvailableSimpleCommands;
// 	int _numberOfSimpleCommands;
// 	SimpleCommand ** _simpleCommands;
// 	char * _outFile;
// 	char * _inputFile;
// 	char * _errFile;
// 	int _background;
// 	void prompt();
// 	void print();
// 	void execute();
// 	void clear();
// 	Command();
// 	void insertSimpleCommand( SimpleCommand * simpleCommand );
// 	static Command _currentCommand;
// 	static SimpleCommand *_currentSimpleCommand;
// };

#endif

 //Felipe struct
//token node

// //token node
// typedef struct s_nod_token
// {
// 	char	*name;
// 	int		flag;
// 	struct s_nod_token	*next;
	
// }	t_nod_token;

// //struct header of the token list
// typedef struct s_list_token
// {
// 	t_nod_token	*head;
// 	int	size;
// }t_list_token;

// typedef sruct s_parsenode
// {
// 	char	type;  // R P C   (Redireccion, Pipe, Commando )
// 	char	redirtype; // - > < + 
// 	char	*file  // soloe relevante para R (Redirecciones -> siempre el primer w. despues de los > >> < <, file1 o )
// 	char	**argv // solo relevante para C (Commando)
// 	s_parsenode	*next;
// } t_parsenode;
