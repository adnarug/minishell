/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:16:01 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/15 17:29:20 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "get_next_line.h"
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

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env *next;
}	t_env;

// typedef struct s_meta{
// 	char	**envp;
	
// } t_meta;

void	execute(char *line_buffer);
int		builtin_echo(char **args_echo);
int		builtin_pwd(char *args_cd);
char	**dup_matrix(char **matrix);
t_env	*ft_head_initializer(char *envp);
t_env	*ft_initializer(char **envp);
void	ft_lstadd_back_mini(t_env **lst, t_env *new);

//Temp functions
void	print_2d(char **array);
int		count_strings(char **array);
char	*ft_cpy_till_eq(char *string);
void	print_env_lst(t_env *env_lst);

//Libft changed
t_env	*ft_lstlast_mini(t_env *lst);
void	ft_lstadd_back_mini(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *value, char *key);

#endif 