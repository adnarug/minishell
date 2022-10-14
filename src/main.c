/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/14 17:47:07 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main (int argc, char **argv, char **envp)
{
	t_input		input;
	char		*line_buffer;
	size_t		len;
	
	while (1)
	{
		line_buffer = NULL;
		len = 0;
		line_buffer = readline("minishell $ ");
		add_history(line_buffer);
		execute(line_buffer);
		free(line_buffer);
	}
}

void	execute(char *line_buffer)
{
	// char	**argv;

	// argv = ft_split(line_buffer, ' ');
	// builtin_echo(argv);
	builtin_pwd(line_buffer);
}