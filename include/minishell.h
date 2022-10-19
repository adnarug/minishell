/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:16:01 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/20 01:05:54 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/param.h> //check if it is fine to include
# include <readline/readline.h>
# include <readline/history.h>




typedef struct s_input
{
	char	*line;
	char	*prompt_name;
}	t_input;

//Linked list for the env
typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env *next;
}	t_env;

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

// DEFINE SEPARATORS:
# define SPACE				' '
# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'
# define DOLLAR				'$'
# define REDIRECT_IN		'<'
# define REDIRECT_OUT		'>'
# define PIPE				'|'
# define SLASH				'/'

//TOKEN FLAGS:
# define T_WORD				1
# define T_REDIRECT_IN		2
# define T_REDIRECT_OUT		3
# define T_APPEND			4
# define T_HEREDOC			5
# define T_PIPE				6

// Mis estructuras
typedef struct s_nod_token
{
	char	*name;
	int		flag;
	struct s_nod_token	*next;
	
}	t_nod_token;

typedef struct s_list_token
{
	t_nod_token	*next;
	int	size;
}t_list_token;


//mis funciones 
void ft_parser(char *lines);
void init_list_token(t_list_token *list);


#endif 