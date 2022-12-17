/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:26:30 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:46:41 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	If the prompt gives us a NULL (equivalent to EOF),
	we print exit and release everything.
	In the case of an empty string, we do not save it in the
	the hitorial but we show the prompt again.
*/
void	data_input(t_minishell *data)
{
	char	*line_prompt;

	data->line = NULL;
	data->input_error = false;
	line_prompt = readline("minishell $ ");
	if (line_prompt == NULL)
		print_error_free_exit(data, ERROR_PRINTED, 1, true);
	if (ft_strlen(line_prompt) != 0)
		add_history(line_prompt);
	data->line = ft_strtrim(line_prompt, SPACE_STRNG);
	free(line_prompt);
	line_prompt = NULL;
	if (ft_strlen(data->line) != 0)
		data->input_error = true;
	else
		free(data->line);
}

void	lex_pars_execut(t_minishell *data)
{
	data_input(data);
	if (data->input_error)
	{
		ft_lexer(data);
		ft_expand(data);
		if (data->lx_error)
		{
			ft_parser(data);
			if (data->prs_error)
			{	
				ft_distribute_parse(data);
				ft_execution(data);
				free_loop_exec(data);
				close(data->std_in);
				close(data->std_out);
			}
		}
		del_parsedtk_and_list_tok(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	initializer_data(&data);
	ft_env(&data, envp);
	while (data.exit_minishell == false)
	{
		signals_main(&(data.termios_default));
		lex_pars_execut(&data);
	}
	close(data.curr_fd_in);
	free_all_exec(&data);
	free_all(&data);
	clear_history();
	return (g_glob_var_exit);
}

/*
	atexit(check_leaks);
*/
void	check_leaks(void)
{
	system("leaks minishell");
}
