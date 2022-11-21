/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:45:57 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/21 23:44:18 by fnieves-         ###   ########.fr       */
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


typedef struct s_cmd
{
	char	*name;
}t_cmd;

typedef struct s_nod_token
{
	char	*name;
	int		flag;//can we rename flag into type?
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
}t_list_token;

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env *next;
}	t_env;
	

//main structur. Here will pend everything but lexing struct
typedef struct s_minishell
{
	char		*line;
	t_env		*env_lst;
	t_list_token	list; //esto hayq eu cambialo a un puntero. Volver a estudiar esto  y diferencia enntre pointer y &
	struct termios	termios_default;
}t_minishell;


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