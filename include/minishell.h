/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:16:01 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/14 17:47:21 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "get_next_line.h"

#include <stdio.h>
#include <sys/param.h> //check if it is fine to include
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_input{
	char	*line;
	char	*prompt_name;
}	t_input;

void	execute(char *line_buffer);
int		builtin_echo(char **args_echo);
int		builtin_pwd(char *args_cd);

#endif 