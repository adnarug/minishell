/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:45:02 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/19 19:27:47 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*

	rl_on_new_line();
	show new prompt and take new  input (prebuild function)
	
	void rl_replace_line (const char *texto1, int clear_undo)
	Replace the contents of rl_line_buffer with texto1

	void rl_redisplay (void)
	Change what’s displayed on the screen
	to reflect the current contents of rl_line_buffer
*/

void	new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0); //probelmas al compilar 
	rl_redisplay();
	glob_var_exit = 1;
}

void	sigquit_main()
{
	struct sigaction	sigac;
	
	sigac.sa_handler = SIG_IGN;
	sigac.sa_flags = SA_RESTART;
	sigemptyset(&sigac.sa_mask);
	sigaction(SIGQUIT, &sigac, NULL);
}


void	sigint_main()
{
	struct sigaction	sigac;

	sigac.sa_handler = &new_prompt;
	sigac.sa_flags = SA_RESTART;
	sigemptyset(&sigac.sa_mask);
	sigaction(SIGINT, &sigac, NULL);
}

/*
 	Behaviour from signals in main process:
 		--> ctrl-c: signal is silenced,no_print_ctrlc, 
		and prints a newline.
 		--> ctrl-backslash: shouldn't do anything
	
	Ctrl+C - SIGINT : 2
	Ctrl+\ - SIGQUIT : 3
*/

void	signals_main(struct termios *per_default)
{
	no_print_ctrlc(per_default);
	sigint_main(); //seguir aqui sabado
	sigquit_main();
}