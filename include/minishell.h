/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:16:01 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/15 16:19:12 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/param.h> //check if it is fine to include
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

#include "struct.h"
#include "error.h"


// typedef struct s_input
// {
// 	char	*line;
// 	char	*prompt_name;
// }	t_input;


void	execute(char *line_buffer);
int		builtin_echo(char **args_echo);
int		builtin_pwd(char *args_cd);
char	**dup_matrix(char **matrix);
t_env	*ft_node_init(char *envp);
t_env	*ft_initializer(char **envp);
void	ft_lstadd_back_mini(t_env **lst, t_env *new);
char	*ft_copy_key(char *string);
void	print_2d(char **array);
int		count_strings(char **array);
void	print_env_lst(t_env *env_lst);
void	ft_lst_free(t_env *lst);
void	ft_free_2d(char **table);
t_env	*ft_lstlast_mini(t_env *lst);
void	ft_lstadd_back_mini(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *value, char *key);


// DE FELIPE
#include <stdint.h> //para trabajr desde casa

// DEFINE SEPARATORS: metacharacter , they will be also used 
//to identify the type of node
# define SPACE				' '
# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'
# define DOLLAR				'$'
# define SLASH				'/'
# define REDIRECT_IN		'<'
# define REDIRECT_OUT		'>'
# define PIPE				'|'
# define APPEND				'+'
# define HEREDOC			'-'
# define WORD				'w'
# define QUOTE_OFF			'\0'

# define	DELIMITERS		" \t|<>"
# define	SPACE_STRNG		" "

//TOKEN FLAGS: //Will not be used ??
# define TYP_WORD				1
# define TYP_REDIRECT_IN		2
# define TYP_REDIRECT_OUT		3
# define TYP_APPEND				4 // >>
# define TYP_HEREDOC			5 //<<
# define TYP_PIPE				6

//TOKEN FLAGS: //Will not be used ??
# define MAIN				1

/* My structures */

//mis funciones 

//para borrar

//void	ft_parser(t_list_token *list, char *line);

void add_toke_list(t_list_token *list, t_nod_token *new);
t_nod_token *create_tok(t_lexing *lex_struct);
t_nod_token *find_last_node(t_list_token *list);
void	delete_list(t_list_token *list);
void init_list_tok(t_list_token *list);
void	creat_lst_tok(t_list_token *list, char **array_w);


//lexer.c

//lexer_token.c

void	initializer_lex(t_lexing *lex_struct);
void	ft_lexer(t_minishell *data);
void	lexer_meta(t_minishell *data, t_lexing *lex_struct);
void	lexer_singl_quot(t_minishell *data, t_lexing *lex_struct);
void	lexer_word(t_minishell *data, t_lexing *lex_struct);
void	lex_redirect(t_minishell *data, t_lexing *lex_struct);
void	find_2nd_quote(t_minishell *data, t_lexing *lex_struct);
void	change_quot_modus(char *quote, char c);
void		ft_isclose_quote(t_minishell *data, t_lexing *lex_struct);



//lexer_tools.c
int ft_isspace(char c);
int ft_ismeta(char c);
int ft_isspecialchar(char c);
int ft_isredirect(char c);


//List tools
void	free_array_list(t_list_token *list, char **array_w);
void	free_array(char **array_w);
void	print_list(t_list_token *list);
void	print_token(t_nod_token	*token);

//Expansion
void	ft_expand(t_minishell *data);
void	expand_find(t_minishell *data, t_nod_token *current);
char	*expand_variable(t_minishell *data , char *buf, char **s_arra);


//Signals
void	signals_execut(int process);


// Expansion tools
int is_not_end_expand(char c);


//Memory leaks
void	check_leaks(void);


void		execute(char *line_buffer);
int			builtin_echo(char **args_echo);
int			builtin_pwd(char *args_cd);
char		**dup_env_matrix(char **matrix);
t_env		*ft_node_init(char *envp);
t_env		*create_env_lst(char **dup_env);
void		ft_lstadd_back_mini(t_env **lst, t_env *new);
char		*ft_copy_key(char *string);
void		print_2d(char **array);
int			count_strings(char **array);
void		print_env_lst(t_env *env_lst);
void		ft_lst_free(t_env *lst);
void		ft_free_2d(char **table);
t_env		*ft_lstlast_mini(t_env *lst);
void		ft_lstadd_back_mini(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(char *key, char *value);
void		ft_lstdelone_env(t_env *node_to_delete, t_env *env);
void		builtin(t_env *env);
void		ft_lstdelone_env(t_env *node_to_delete, t_env *env);
t_env		*ft_lst_find(t_env *node, char *key);
t_env		*ft_lst_find_previous(t_env *head, t_env *node_to_find);
int			ft_strcmp(const char *s1, const char *s2);
int		ft_execution(t_minishell *data);

void	ft_env(t_minishell *data, char **envp);

void	print_env_lst_export(t_env *env_lst);


//Refactored libft
char		**split_into_key_value(char *string);
long int	ft_atol(const char *str);

//Builtins
int		builtin_env(t_env *env, char *argv) ;
int		builtin_cd(t_env *env, char **argv);
int		builtin_unset(t_env *env, char **argv);
int		builtin_export(t_env *envp, char **argv);
int		builtin_exit(char	**token);

//Execution 
int	is_builtin(t_nod_token *token, t_minishell *data);
int 	cmd_exec(t_nod_token *token, t_minishell *data);
int	    exec_builtin(t_nod_token *token_node, t_minishell *data);
int		ft_execution(t_minishell *data);
char    **init_builtins_arr(char **builtins);
int		find_correct_paths(t_nod_token *parameters, t_minishell *data);
char	**find_path(char **envp);
char	*check_paths(char **path_to_builtins, char	*command);
char	**add_path_sign(char **path_to_builtins);
#endif 